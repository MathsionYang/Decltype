#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
namespace CPlus
{
	namespace ThreadPool
	{
		class ThreadPool
		{
		public:
			ThreadPool(size_t nSize);
			~ThreadPool();
			template<class F, class... Args>
			auto Enqueue(F&& f, Args&&... args)
				->std::future<typename std::result_of<F(Args...)>::type>;
		private:
			std::vector< std::thread > vecThread;
		public:
			std::mutex queue_mutex;
			std::queue< std::function<void()> > taskQueue;
			std::condition_variable condition;
			bool stop;
		};

		template<class F, class... Args>
		auto CPlus::ThreadPool::ThreadPool::Enqueue(F&& f, Args&&... args) ->std::future<typename std::result_of<F(Args...)>::type>
		{
			using return_type = typename std::result_of<F(Args...)>::type;
			auto task = std::make_shared< std::packaged_task<return_type()> >(
				std::bind(std::forward<F>(f), std::forward<Args>(args)...)
				);
			std::future<return_type> res = task->get_future();
			{
				std::unique_lock<std::mutex> lock(queue_mutex);

				// don't allow enqueueing after stopping the pool
				if (stop)
					throw std::runtime_error("enqueue on stopped ThreadPool");

				taskQueue.emplace([task]() { (*task)(); });
			}
			condition.notify_one();
			return res;
		}

		class TaskExecutor
		{
		public:
			TaskExecutor(ThreadPool& pool) : threadPool(pool) {}

			void operator()()
			{
				for (;;)
				{
					std::function<void()> task;

					{
						std::unique_lock<std::mutex> lock(threadPool.queue_mutex);
						threadPool.condition.wait(lock, [this] { return threadPool.stop || !threadPool.taskQueue.empty(); });

						if (threadPool.stop && threadPool.taskQueue.empty())
							return;

						task = std::move(threadPool.taskQueue.front());
						threadPool.taskQueue.pop();
					}

					task();
				}
			}

		private:
			ThreadPool& threadPool;
		};



	}
}

