#pragma once
#include "CPlus/Global.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <memory>

/// <summary>
/// ���������������ã�Ϊ�˱����ڴ�й©�������ǵ������л���ָ���Ա����ʱ�Ż�ʹ�õ���
/// ������������ʹ����ɾ��ָ���������Ļ���ָ��ʱ��
/// ���Ե������������������ʵ���ͷ������ж��ڴ��Ŀ�ģ��Ӷ���ֹ�ڴ�й©��
/// ʹ�� volatile �ؼ��������ı��������������ԣ��ױ�ġ������Ż��ġ�˳��ִ�е�
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
			volatile std::atomic_bool pauseFlag;   ///<��ͣ��ʶ
			volatile std::atomic_bool stopFlag;   ///<ֹͣ��ʶ
			Status m_Status;
		};


	}
}

