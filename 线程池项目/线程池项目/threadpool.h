#ifndef THREADPOOL_H   // 如果没有定义 THREADPOOL_H
#define THREADPOOL_H   // 定义 THREADPOOL_H
// 头文件内容
#include <vector>
#include <queue>
#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>

// 任务抽象的基类
class Task
{
public:
	// 用户可以自定义任意任务类型，从Task继承，重写run方法，实现自定义任务处理
	virtual void run() = 0;
};

//线程池支持的模式
enum class PoolMode
{
	MODE_FIXED,  //固定数量的线程
	MODE_CACHED, //线程数量动态增长

};

//线程类型
class Thread 
{
public:
	//启动线程
	void start();
private:
};


// 线程池类型
class ThreadPool 
{
public:
	ThreadPool();
	~ThreadPool();

	//设置线程池的工作模式
	void setMode(PoolMode mode);

	//设置task任务队列上线阈值
	void setTaskQueMaxThreshHold(int threshhold);

	//给线程池提交任务
	void submitTask(std::shared_ptr<Task> sp);

	//开启线程池
	void start(int initThreadSize =4);

	//不希望用户对线程池对象本身进行拷贝构造和赋值
	ThreadPool(const ThreadPool&) = delete; //禁用拷贝构造函数：
	ThreadPool& operator=(const ThreadPool&) = delete; //禁用拷贝赋值运算符

private:
	//定义线程函数
	void threadFunc();
	

private:
	std::vector<Thread*> threads_; //线程列表
	int  initThreadSize_;   //初始的线程数量

	//这里之所以用智能指针是因为：用户可能只是创建了临时的任务对象，当任务执行完后对象就析构了
	// 所以这里需要考虑 “用户传入的任务对象的生命周期”，所以这里不能用裸指针,要用强智能指针，拉长任务对象的生命周期
	// std::queue<Task*> 
	std::queue<std::shared_ptr<Task>> taskQueue_; //任务队列

	//有多个线程都会读写任务数量（一个线程++，另一个线程--），所以这里用原子类型保证变量线程安全
	std::atomic_int taskSize_; //记录任务数量

	int taskSizeThreshHold_;  //任务数量阈值
	std::mutex taskQueMtx_; //保证任务队列的线程安全
	std::condition_variable notFull_;  //表示任务队列不满
	std::condition_variable notEmpty_; //表示任务队列不空 
	PoolMode poolMode_; //当前线程池的工作模式
   
	
};



#endif     // 结束条件编译
