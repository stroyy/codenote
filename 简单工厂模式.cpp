#include <iostream>


using namespace std;
//��Ʒ��ĸ���
class AbstractSmile {
public:
	virtual void transform() = 0;
	virtual void ability() = 0;
	virtual ~AbstractSmile() {};
};

class SheepSmile :public AbstractSmile {
public:
	void transform()override {
		cout << "ɽ����̬..." << endl;
	};
	void ability() override {
		cout << "ɽ������..." << endl;
	};
};

class LionSmile :public AbstractSmile {
public:
	void transform()override {
		cout << "ʨ����̬..." << endl;
	};
	void ability() override {
		cout << "ʨ������..." << endl;
	};
};

class BatSmile :public AbstractSmile {
public:
	void transform()override {
		cout << "������̬..." << endl;
	};
	void ability() override {
		cout << "��������..." << endl;
	};
};

//���幤���ࣨ�򵥹���ģʽ�¹��������ҽ���һ����
enum class Type :char { Sheep, Lion, Bat }; //ǿ����ö�٣���class����struct�ؼ���,ǿ�����������ָ��ö���ڵײ��Ӧ�����ͣ�
class SmileFactory {
public:
	AbstractSmile* createSmile(Type type) {
		AbstractSmile* ptr = nullptr;
		switch (type) {
		case Type::Sheep:
			ptr = new SheepSmile;
			break;
		case Type::Lion:
			ptr = new LionSmile;
			break;
		case Type::Bat:
			ptr = new BatSmile;
			break;
		default:
			break;
		}
		return ptr;
	}
};
int main() {
	SmileFactory* factory = new SmileFactory;
	AbstractSmile* obj = factory->createSmile(Type::Lion);
	obj->transform();
	obj->ability();
	delete factory;
	delete obj;
	return 0;
}
