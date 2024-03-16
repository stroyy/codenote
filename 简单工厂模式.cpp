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

//定义工厂类（简单工厂模式下工厂类有且仅有一个）
enum class Type :char { Sheep, Lion, Bat }; //强类型枚举（有class或者struct关键字,强类型美剧可以指定枚举在底层对应的类型）
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
