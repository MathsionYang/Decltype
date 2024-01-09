#include "ThreadPool.h"
namespace CPlus
{
	namespace ThreadPool
	{

		ThreadPool::ThreadPool(size_t nSize) : stop(false)
		{
			for (size_t i = 0; i < nSize; ++i)
			{
				vecThread.emplace_back(TaskExecutor(*this));
			}
		}

		ThreadPool::~ThreadPool()
		{
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				stop = true;
			}
			condition.notify_all();
			for (std::thread& thred : vecThread)
				thred.join();
		}

		/*
		* int taskFunction(int i)
{
	std::cout << "hello " << i << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "world " << i << std::endl;
	return i * i;
}

int main()
{
	ThreadPool pool(4);
	std::vector<std::future<int>> results;
	const int numTasks = 8;

	for(int i = 0; i < numTasks; ++i) {
		// Enqueue the task function to the thread pool
		auto task = std::bind(taskFunction, i);
		results.emplace_back(pool.enqueue(task));
	}

	for(auto && result : results)
		std::cout << result.get() << ' ';
	std::cout << std::endl;

	return 0;
}
		*/
	}
}