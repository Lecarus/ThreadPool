#ifndef THREADPOOL_H   // ���û�ж��� THREADPOOL_H
#define THREADPOOL_H   // ���� THREADPOOL_H
// ͷ�ļ�����
#include <vector>
#include <queue>
#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>

// �������Ļ���
class Task
{
public:
	// �û������Զ��������������ͣ���Task�̳У���дrun������ʵ���Զ���������
	virtual void run() = 0;
};

//�̳߳�֧�ֵ�ģʽ
enum class PoolMode
{
	MODE_FIXED,  //�̶��������߳�
	MODE_CACHED, //�߳�������̬����

};

//�߳�����
class Thread 
{
public:
	//�����߳�
	void start();
private:
};


// �̳߳�����
class ThreadPool 
{
public:
	ThreadPool();
	~ThreadPool();

	//�����̳߳صĹ���ģʽ
	void setMode(PoolMode mode);

	//����task�������������ֵ
	void setTaskQueMaxThreshHold(int threshhold);

	//���̳߳��ύ����
	void submitTask(std::shared_ptr<Task> sp);

	//�����̳߳�
	void start(int initThreadSize =4);

	//��ϣ���û����̳߳ض�������п�������͸�ֵ
	ThreadPool(const ThreadPool&) = delete; //���ÿ������캯����
	ThreadPool& operator=(const ThreadPool&) = delete; //���ÿ�����ֵ�����

private:
	//�����̺߳���
	void threadFunc();
	

private:
	std::vector<Thread*> threads_; //�߳��б�
	int  initThreadSize_;   //��ʼ���߳�����

	//����֮����������ָ������Ϊ���û�����ֻ�Ǵ�������ʱ��������󣬵�����ִ���������������
	// ����������Ҫ���� ���û���������������������ڡ����������ﲻ������ָ��,Ҫ��ǿ����ָ�룬��������������������
	// std::queue<Task*> 
	std::queue<std::shared_ptr<Task>> taskQueue_; //�������

	//�ж���̶߳����д����������һ���߳�++����һ���߳�--��������������ԭ�����ͱ�֤�����̰߳�ȫ
	std::atomic_int taskSize_; //��¼��������

	int taskSizeThreshHold_;  //����������ֵ
	std::mutex taskQueMtx_; //��֤������е��̰߳�ȫ
	std::condition_variable notFull_;  //��ʾ������в���
	std::condition_variable notEmpty_; //��ʾ������в��� 
	PoolMode poolMode_; //��ǰ�̳߳صĹ���ģʽ
   
	
};



#endif     // ������������
