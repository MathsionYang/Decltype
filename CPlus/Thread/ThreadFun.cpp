#include "ThreadFun.h"
namespace CPlus
{
	namespace Thread
	{

		ThreadFun::ThreadFun(std::function<void(int)>func, int nTaskId)
			:m_threadPtr(nullptr), m_nTaskID(nTaskId),
			m_Status(Status::Stoped), pauseFlag(false), stopFlag(false)
		{
			m_Process = func;
		}

		ThreadFun::~ThreadFun()
		{
			StopThread();
		}

		CPlus::Thread::Status ThreadFun::GetThreadStatus() const
		{
			return m_Status;
		}

		void ThreadFun::StartThread()
		{
			if (m_threadPtr == nullptr)
			{
				m_threadPtr = std::make_shared<std::thread>(&ThreadFun::Run, this);
				pauseFlag = false;
				stopFlag = false;
				m_Status = Status::Running;
			}
		}

		void ThreadFun::StopThread()
		{
			if (m_threadPtr != nullptr)
			{
				pauseFlag = false;
				stopFlag = true;
				m_condition.notify_all();  // Notify one waiting thread, if there is one.
				if (m_threadPtr->joinable())
					m_threadPtr->join(); // wait for thread finished
				
				m_Status = Status::Stoped;
			}

		}

		void ThreadFun::PauseThread()
		{
			if (m_threadPtr != nullptr)
			{
				pauseFlag = true;
				m_Status = Status::Paused;
			}
		}

		void ThreadFun::ResumeThread()
		{
			if (m_threadPtr != nullptr)
			{
				pauseFlag = false;
				m_condition.notify_all();
				m_Status = Status::Running;
			}

		}

		bool ThreadFun::CheckStop()
		{
			return stopFlag;
		}

		bool ThreadFun::WaitPause()
		{
			if (pauseFlag)
			{
				std::unique_lock<std::mutex> locker(m_mutex);
				while (pauseFlag)
				{
					m_condition.wait(locker); // Unlock _mutex and wait to be notified
				}
				locker.unlock();
			}

			return !stopFlag;

		}

		void ThreadFun::Run()
		{
			m_Process(m_nTaskID);
			pauseFlag = false;
			stopFlag = false;
		}

	}
}