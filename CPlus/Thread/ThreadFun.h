#pragma once
#include "CPlus/Global.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <memory>

/// <summary>
/// 虚析构函数的作用：为了避免内存泄漏，而且是当子类中会有指针成员变量时才会使用到。
/// 即虚析构函数使得在删除指向子类对象的基类指针时，
/// 可以调用子类的析构函数来实现释放子类中堆内存的目的，从而防止内存泄漏。
/// 使用 volatile 关键字声明的变量具有三种特性：易变的、不可优化的、顺序执行的
/// </summary>
namespace CPlus
{
	namespace Thread
	{
		enum class Status
		{
			Stoped = 0,
			Running,
			Paused,
			Waiting
		};


		class ThreadFun
		{
		public:
			ThreadFun(std::function<void(int)>func, int nTaskId);
			virtual ~ThreadFun();

		public:
			Status GetThreadStatus() const;

			void StartThread();
			void StopThread();
			void PauseThread();
			void ResumeThread();

			bool CheckStop();
			bool WaitPause();
		private:
			void Run();
		private:
			std::function<void(int)>m_Process;
			int m_nTaskID;
			std::shared_ptr<std::thread>m_threadPtr;
			std::mutex m_mutex;
			std::condition_variable m_condition;
			volatile std::atomic_bool pauseFlag;   ///<暂停标识
			volatile std::atomic_bool stopFlag;   ///<停止标识
			Status m_Status;
		};


	}
}

