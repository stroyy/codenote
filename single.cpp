#include <chrono>
#include <iostream>
#include <mutex>
#include <atomic> //原子变量 
#include <queue>
#include <thread>

using namespace std;

#if 0
//饿汉模式
//定义一个单例模式的任务队列
class TaskQueue {
public:
	//TaskQueue()=delete;   //默认的构造函数
	TaskQueue(const TaskQueue& t) = delete;   //拷贝构造函数
	TaskQueue& operator = (const TaskQueue& t) = delete; //复制赋值运算符创建新的实例
	static TaskQueue* getInstance() {
		return m_taskQ;
	}

	void Print() {
		cout << "我是饿汉模式单例对象中的一个成员函数。。。" << endl;
	}
private:
	//访问控制权限设为private就不能通过下面的构造函数和赋值运算符创建新对象
	TaskQueue() = default;
	// TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default; 

	//只能通过类名访问静态成员或属性
	static TaskQueue* m_taskQ;
};

TaskQueue* TaskQueue::m_taskQ = new TaskQueue; //饿汉模式

#else  

#if 0
//定义一个单例模式的任务队列
//懒汉模式
//使用互斥锁+原子变量方式来解决线程不安全的问题
class TaskQueue {
public:
	//TaskQueue()=delete;   //默认的构造函数
	TaskQueue(const TaskQueue& t) = delete;   //拷贝构造函数
	TaskQueue& operator = (const TaskQueue& t) = delete; //复制赋值运算符创建新的实例

	static TaskQueue* getInstance() {
		TaskQueue* task = m_taskQ.load();
		if (task == nullptr) {
			m_mutex.lock();
			task = m_taskQ.load();
			if (task == nullptr) {
				task = new TaskQueue;
				m_taskQ.store(task);
			}
			m_mutex.unlock();
		}
		return task;
	}
	void Print() {
		cout << "我是懒汉模式单例对象中的一个成员函数。。。" << endl;
	}
private:
	//访问控制权限设为private就不能通过下面的构造函数和赋值运算符创建新对象
	TaskQueue() = default;
	// TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default; 

	//只能通过类名访问静态成员或属性
	// static TaskQueue * m_taskQ; 
	static mutex m_mutex;
	static atomic<TaskQueue*> m_taskQ;
};

atomic<TaskQueue* >TaskQueue::m_taskQ;
mutex TaskQueue::m_mutex;

#endif

#if 0
//懒汉模式
//使用静态局部变量的方式解决线程不安全问题
class TaskQueue {
public:
	//TaskQueue()=delete;   //默认的构造函数
	TaskQueue(const TaskQueue& t) = delete;   //拷贝构造函数
	TaskQueue& operator = (const TaskQueue& t) = delete; //复制赋值运算符创建新的实例

	static TaskQueue* getInstance() {
		static TaskQueue taskQ;
		return &taskQ;
	}
	void Print() {
		cout << "我是懒汉模式单例对象中的一个成员函数。。。" << endl;
	}
private:
	//访问控制权限设为private就不能通过下面的构造函数和赋值运算符创建新对象
	TaskQueue() = default;
	// TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default; 

	//只能通过类名访问静态成员或属性


};

#endif

#if 1
//写一个任务队列
class TaskQueue {
public:
	//TaskQueue()=delete;   //默认的构造函数
	TaskQueue(const TaskQueue& t) = delete;   //拷贝构造函数
	TaskQueue& operator = (const TaskQueue& t) = delete; //复制赋值运算符创建新的实例
	static TaskQueue* getInstance() {
		return m_taskQ;
	}

	void Print() {
		cout << "我是饿汉模式单例对象中的一个成员函数。。。" << endl;
	}

	//判断任务队列是否为空
	bool isEmpty() {
		lock_guard<mutex> locker(m_mutex);
		bool flag = m_data.empty();
		return flag;
	}

	//添加任务
	void addTask(int node) {
		lock_guard<mutex> locker(m_mutex);
		m_data.push(node);
	}

	//删除任务
	bool popTask() {
		lock_guard<mutex> locker(m_mutex);
		if (m_data.empty()) {
			return false;
		}
		m_data.pop();
		return true;
	}

	//取出一个任务(不删除任务)
	int takeTask() {
		lock_guard<mutex> locker(m_mutex);
		if (m_data.empty()) {
			return -1;
		}
		int data = m_data.front();
		return data;
	}
private:
	//访问控制权限设为private就不能通过下面的构造函数和赋值运算符创建新对象
	TaskQueue() = default;
	// TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default; 

	//只能通过类名访问静态成员或属性
	static TaskQueue* m_taskQ;
	mutex m_mutex;
	//定义任务队列
	queue<int> m_data;
};

TaskQueue* TaskQueue::m_taskQ = new TaskQueue; //饿汉模式


#endif



#endif
int main() {
	TaskQueue* taskQ = TaskQueue::getInstance();
	//生产者
	thread t1([=]() {
		for (int i = 0; i < 100; ++i) {
			taskQ->addTask(i + 100);
			cout << "+++ push data: " << i + 100 << ", ThreadId: " << this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::milliseconds(500));
		}
		});
	//消费者
	thread t2([=]() {
		this_thread::sleep_for(chrono::milliseconds(100));
		while (!taskQ->isEmpty()) {
			int num = taskQ->takeTask();
			cout << "+++ take task: " << num << "ThreadID: " << this_thread::get_id() << endl;
			taskQ->popTask();
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
		});
	t1.join();
	t2.join();
	return 0;
}
