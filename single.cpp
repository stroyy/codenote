#include <chrono>
#include <iostream>
#include <mutex>
#include <atomic> //ԭ�ӱ��� 
#include <queue>
#include <thread>

using namespace std;

#if 0
//����ģʽ
//����һ������ģʽ���������
class TaskQueue {
public:
	//TaskQueue()=delete;   //Ĭ�ϵĹ��캯��
	TaskQueue(const TaskQueue& t) = delete;   //�������캯��
	TaskQueue& operator = (const TaskQueue& t) = delete; //���Ƹ�ֵ����������µ�ʵ��
	static TaskQueue* getInstance() {
		return m_taskQ;
	}

	void Print() {
		cout << "���Ƕ���ģʽ���������е�һ����Ա����������" << endl;
	}
private:
	//���ʿ���Ȩ����Ϊprivate�Ͳ���ͨ������Ĺ��캯���͸�ֵ����������¶���
	TaskQueue() = default;
	// TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default; 

	//ֻ��ͨ���������ʾ�̬��Ա������
	static TaskQueue* m_taskQ;
};

TaskQueue* TaskQueue::m_taskQ = new TaskQueue; //����ģʽ

#else  

#if 0
//����һ������ģʽ���������
//����ģʽ
//ʹ�û�����+ԭ�ӱ�����ʽ������̲߳���ȫ������
class TaskQueue {
public:
	//TaskQueue()=delete;   //Ĭ�ϵĹ��캯��
	TaskQueue(const TaskQueue& t) = delete;   //�������캯��
	TaskQueue& operator = (const TaskQueue& t) = delete; //���Ƹ�ֵ����������µ�ʵ��

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
		cout << "��������ģʽ���������е�һ����Ա����������" << endl;
	}
private:
	//���ʿ���Ȩ����Ϊprivate�Ͳ���ͨ������Ĺ��캯���͸�ֵ����������¶���
	TaskQueue() = default;
	// TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default; 

	//ֻ��ͨ���������ʾ�̬��Ա������
	// static TaskQueue * m_taskQ; 
	static mutex m_mutex;
	static atomic<TaskQueue*> m_taskQ;
};

atomic<TaskQueue* >TaskQueue::m_taskQ;
mutex TaskQueue::m_mutex;

#endif

#if 0
//����ģʽ
//ʹ�þ�̬�ֲ������ķ�ʽ����̲߳���ȫ����
class TaskQueue {
public:
	//TaskQueue()=delete;   //Ĭ�ϵĹ��캯��
	TaskQueue(const TaskQueue& t) = delete;   //�������캯��
	TaskQueue& operator = (const TaskQueue& t) = delete; //���Ƹ�ֵ����������µ�ʵ��

	static TaskQueue* getInstance() {
		static TaskQueue taskQ;
		return &taskQ;
	}
	void Print() {
		cout << "��������ģʽ���������е�һ����Ա����������" << endl;
	}
private:
	//���ʿ���Ȩ����Ϊprivate�Ͳ���ͨ������Ĺ��캯���͸�ֵ����������¶���
	TaskQueue() = default;
	// TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default; 

	//ֻ��ͨ���������ʾ�̬��Ա������


};

#endif

#if 1
//дһ���������
class TaskQueue {
public:
	//TaskQueue()=delete;   //Ĭ�ϵĹ��캯��
	TaskQueue(const TaskQueue& t) = delete;   //�������캯��
	TaskQueue& operator = (const TaskQueue& t) = delete; //���Ƹ�ֵ����������µ�ʵ��
	static TaskQueue* getInstance() {
		return m_taskQ;
	}

	void Print() {
		cout << "���Ƕ���ģʽ���������е�һ����Ա����������" << endl;
	}

	//�ж���������Ƿ�Ϊ��
	bool isEmpty() {
		lock_guard<mutex> locker(m_mutex);
		bool flag = m_data.empty();
		return flag;
	}

	//�������
	void addTask(int node) {
		lock_guard<mutex> locker(m_mutex);
		m_data.push(node);
	}

	//ɾ������
	bool popTask() {
		lock_guard<mutex> locker(m_mutex);
		if (m_data.empty()) {
			return false;
		}
		m_data.pop();
		return true;
	}

	//ȡ��һ������(��ɾ������)
	int takeTask() {
		lock_guard<mutex> locker(m_mutex);
		if (m_data.empty()) {
			return -1;
		}
		int data = m_data.front();
		return data;
	}
private:
	//���ʿ���Ȩ����Ϊprivate�Ͳ���ͨ������Ĺ��캯���͸�ֵ����������¶���
	TaskQueue() = default;
	// TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default; 

	//ֻ��ͨ���������ʾ�̬��Ա������
	static TaskQueue* m_taskQ;
	mutex m_mutex;
	//�����������
	queue<int> m_data;
};

TaskQueue* TaskQueue::m_taskQ = new TaskQueue; //����ģʽ


#endif



#endif
int main() {
	TaskQueue* taskQ = TaskQueue::getInstance();
	//������
	thread t1([=]() {
		for (int i = 0; i < 100; ++i) {
			taskQ->addTask(i + 100);
			cout << "+++ push data: " << i + 100 << ", ThreadId: " << this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::milliseconds(500));
		}
		});
	//������
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
