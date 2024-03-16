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

//���幤����-����
class AbstractFactory {
public:
	virtual AbstractSmile* createSmile() = 0;
	virtual ~AbstractFactory() {}
};

//����SheepSmile
class SheepFactory :public AbstractFactory {
public:
	AbstractSmile* createSmile() {
		return new SheepSmile;
	}
	~SheepFactory() {
		cout << "SheepFactory ��������..." << endl;
	}
};

//����LionSmile
class LionFactory :public AbstractFactory {
public:
	AbstractSmile* createSmile() {
		return new LionSmile;
	}
	~LionFactory() {
		cout << "LionFactory ��������..." << endl;
	}
};

//����LionSmile
class BatFactory :public AbstractFactory {
public:
	AbstractSmile* createSmile() {
		return new BatSmile;
	}
	~BatFactory() {
		cout << "BatFactory ��������..." << endl;
	}
};
int main() {
	AbstractFactory* factoy = new SheepFactory;
	AbstractSmile* obj = factoy->createSmile();
	obj->transform();
	obj->ability();
	delete factoy;;
	delete obj;

	return 0;
}