#include <iostream>
#include <pthread.h>

using namespace std;

//船体
class ShipBody {
public:
	virtual string getBody() = 0;
	virtual ~ShipBody() {}
};
//木头船体
class WoodBody :public ShipBody {
public:
	string getBody() override {
		return string("使用<木材>制作船体...");
	}
};
class IronBody :public ShipBody {
public:
	string getBody() override {
		return string("使用<钢铁>制作船体...");
	}
};
class MetalBody :public ShipBody {
public:
	string getBody() override {
		return string("使用<合成金属>制作船体...");
	}
};
//引擎
class Engine {
public:
	virtual string getEngine() = 0;
	virtual ~Engine() {}
};
class Human :public Engine {
public:
	string getEngine() override {
		return string("动力方式是<手动>...");
	}
};
class Diesel :public Engine {
public:
	string getEngine() override {
		return string("动力方式是<内燃机>...");
	}
};
class Nuclear :public Engine {
public:
	string getEngine() override {
		return string("动力方式是<核反应堆>...");
	}
};
//武器
class Weapon {
public:
	virtual string getWeapon() = 0;
	virtual ~Weapon() {}
};

class Gun :public Weapon {
public:
	string getWeapon() override {
		return string("船上的武器系统是<枪>...");
	}
};
class Cannon :public Weapon {
public:
	string getWeapon() override {
		return string("船上的武器系统是<加农炮>...");
	}
};
class Laser :public Weapon {
public:
	string getWeapon() override {
		return string("船上的武器系统是<激光枪  >...");
	}
};

//船
class Ship {
public:
	Ship(ShipBody* body, Engine* engine, Weapon* weapon) :
		m_body(body), m_engine(engine), m_weapon(weapon) {}

	~Ship() {
		delete m_body;
		delete m_engine;
		delete m_weapon;
	}
	string getProperty() {
		string info = m_body->getBody() + m_engine->getEngine() + m_weapon->getWeapon();
		return info;
	}
private:
	ShipBody* m_body;
	Engine* m_engine;
	Weapon* m_weapon;
};

//工厂类——抽象
class AbstractFactory {
public:
	virtual Ship* createShip() = 0;
	virtual ~AbstractFactory() {}
};
class BasicFactory :public AbstractFactory {
public:
	Ship* createShip()override {
		Ship* ship = new Ship(new WoodBody, new Human, new Gun);
		cout << "<基础型的船>建造完毕！！！" << endl;
		return ship;
	}
};
class StandardFactory :public AbstractFactory {
public:
	Ship* createShip()override {
		Ship* ship = new Ship(new IronBody, new Diesel, new Cannon);
		cout << "<标准型的船>建造完毕！！！" << endl;
		return ship;
	}
};
class UltimataFactory :public AbstractFactory {
public:
	Ship* createShip()override {
		Ship* ship = new Ship(new MetalBody, new Nuclear, new Laser);
		cout << "<旗舰型的船>建造完毕！！！" << endl;
		return ship;
	}
};
int main() {
	//旗舰型的船
	AbstractFactory* factoy = new UltimataFactory;
	Ship* ship = factoy->createShip();
	string info = ship->getProperty();
	cout << info << endl;

	delete ship;
	delete factoy;
	return 0;
}