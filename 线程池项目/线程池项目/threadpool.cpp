#include "threadpool.h"
#include<functional>

const int TASK_MAX_THRESHHOLD = 1024;

//�̳߳ع���
ThreadPool::ThreadPool()
	: initThreadSize_(0),
	taskSize_(0),
	taskSizeThreshHold_(TASK_MAX_THRESHHOLD),
	poolMode_(PoolMode::MODE_FIXED)
{}

//�̳߳�����
ThreadPool:: ~ThreadPool()
{}

//�����̳߳صĹ���ģʽ
void ThreadPool::setMode(PoolMode mode) 
{
	poolMode_ = mode;
}


//����task�������������ֵ
void ThreadPool::setTaskQueMaxThreshHold(int threshhold)
{
	taskSizeThreshHold_ = threshhold;
}

//���̳߳��ύ����
void ThreadPool::submitTask(std::shared_ptr<Task> sp)
{

}

//�����̳߳�
void ThreadPool::start(int initThreadSize)
{
	//��¼��ʼ�߳�����
	initThreadSize_ = initThreadSize;

	//�����̶߳���
	for (int i = 0; i < initThreadSize_; i++)
	{
		//�����̶߳����ʱ����̺߳�������thread�̶߳���
		threads_.emplace_back(new Thread(std::bind(&ThreadPool::threadFunc,this)));
	}

	//���������߳�
	for (int i = 0; i < initThreadSize_; i++)
	{
		threads_[i]->start(); //�̵߳�������Ҫִ��һ���̺߳���
	}
}

void ThreadPool::threadFunc()
{

}

/*----------�̷߳���ʵ��-----------*/
//�����߳�
void Thread::start()
{

}