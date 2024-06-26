#include "threadpool.h"
#include<functional>

const int TASK_MAX_THRESHHOLD = 1024;

//线程池构造
ThreadPool::ThreadPool()
	: initThreadSize_(0),
	taskSize_(0),
	taskSizeThreshHold_(TASK_MAX_THRESHHOLD),
	poolMode_(PoolMode::MODE_FIXED)
{}

//线程池析构
ThreadPool:: ~ThreadPool()
{}

//设置线程池的工作模式
void ThreadPool::setMode(PoolMode mode) 
{
	poolMode_ = mode;
}


//设置task任务队列上线阈值
void ThreadPool::setTaskQueMaxThreshHold(int threshhold)
{
	taskSizeThreshHold_ = threshhold;
}

//给线程池提交任务
void ThreadPool::submitTask(std::shared_ptr<Task> sp)
{

}

//开启线程池
void ThreadPool::start(int initThreadSize)
{
	//记录初始线程数量
	initThreadSize_ = initThreadSize;

	//创建线程对象
	for (int i = 0; i < initThreadSize_; i++)
	{
		//创建线程对象的时候把线程函数给到thread线程对象
		threads_.emplace_back(new Thread(std::bind(&ThreadPool::threadFunc,this)));
	}

	//启动所有线程
	for (int i = 0; i < initThreadSize_; i++)
	{
		threads_[i]->start(); //线程的启动是要执行一个线程函数
	}
}

void ThreadPool::threadFunc()
{

}

/*----------线程方法实现-----------*/
//启动线程
void Thread::start()
{

}