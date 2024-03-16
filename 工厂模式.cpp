#include <iostream>

using namespace std;
//产品类的父类
class AbstractSmile {
public:
	virtual void transform() = 0;
	virtual void ability() = 0;
	virtual ~AbstractSmile() {};
};

class SheepSmile :public AbstractSmile {
public:
	void transform()override {
		cout << "山羊形态..." << endl;
	};
	void ability() override {
		cout << "山羊能力..." << endl;
	};
};

class LionSmile :public AbstractSmile {
public:
	void transform()override {
		cout << "狮子形态..." << endl;
	};
	void ability() override {
		cout << "狮子能力..." << endl;
	};
};

class BatSmile :public AbstractSmile {
public:
	void transform()override {
		cout << "蝙蝠形态..." << endl;
	};
	void ability() override {
		cout << "蝙蝠能力..." << endl;
	};
};

//定义工厂类-父类
class AbstractFactory {
public:
	virtual AbstractSmile* createSmile() = 0;
	virtual ~AbstractFactory() {}
};

//生产SheepSmile
class SheepFactory :public AbstractFactory {
public:
	AbstractSmile* createSmile() {
		return new SheepSmile;
	}
	~SheepFactory() {
		cout << "SheepFactory 被析构了..." << endl;
	}
};

//生产LionSmile
class LionFactory :public AbstractFactory {
public:
	AbstractSmile* createSmile() {
		return new LionSmile;
	}
	~LionFactory() {
		cout << "LionFactory 被析构了..." << endl;
	}
};

//生产LionSmile
class BatFactory :public AbstractFactory {
public:
	AbstractSmile* createSmile() {
		return new BatSmile;
	}
	~BatFactory() {
		cout << "BatFactory 被析构了..." << endl;
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