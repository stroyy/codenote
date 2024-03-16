#include <iostream>
#include <pthread.h>

using namespace std;

//����
class ShipBody {
public:
	virtual string getBody() = 0;
	virtual ~ShipBody() {}
};
//ľͷ����
class WoodBody :public ShipBody {
public:
	string getBody() override {
		return string("ʹ��<ľ��>��������...");
	}
};
class IronBody :public ShipBody {
public:
	string getBody() override {
		return string("ʹ��<����>��������...");
	}
};
class MetalBody :public ShipBody {
public:
	string getBody() override {
		return string("ʹ��<�ϳɽ���>��������...");
	}
};
//����
class Engine {
public:
	virtual string getEngine() = 0;
	virtual ~Engine() {}
};
class Human :public Engine {
public:
	string getEngine() override {
		return string("������ʽ��<�ֶ�>...");
	}
};
class Diesel :public Engine {
public:
	string getEngine() override {
		return string("������ʽ��<��ȼ��>...");
	}
};
class Nuclear :public Engine {
public:
	string getEngine() override {
		return string("������ʽ��<�˷�Ӧ��>...");
	}
};
//����
class Weapon {
public:
	virtual string getWeapon() = 0;
	virtual ~Weapon() {}
};

class Gun :public Weapon {
public:
	string getWeapon() override {
		return string("���ϵ�����ϵͳ��<ǹ>...");
	}
};
class Cannon :public Weapon {
public:
	string getWeapon() override {
		return string("���ϵ�����ϵͳ��<��ũ��>...");
	}
};
class Laser :public Weapon {
public:
	string getWeapon() override {
		return string("���ϵ�����ϵͳ��<����ǹ  >...");
	}
};

//��
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

//�����ࡪ������
class AbstractFactory {
public:
	virtual Ship* createShip() = 0;
	virtual ~AbstractFactory() {}
};
class BasicFactory :public AbstractFactory {
public:
	Ship* createShip()override {
		Ship* ship = new Ship(new WoodBody, new Human, new Gun);
		cout << "<�����͵Ĵ�>������ϣ�����" << endl;
		return ship;
	}
};
class StandardFactory :public AbstractFactory {
public:
	Ship* createShip()override {
		Ship* ship = new Ship(new IronBody, new Diesel, new Cannon);
		cout << "<��׼�͵Ĵ�>������ϣ�����" << endl;
		return ship;
	}
};
class UltimataFactory :public AbstractFactory {
public:
	Ship* createShip()override {
		Ship* ship = new Ship(new MetalBody, new Nuclear, new Laser);
		cout << "<�콢�͵Ĵ�>������ϣ�����" << endl;
		return ship;
	}
};
int main() {
	//�콢�͵Ĵ�
	AbstractFactory* factoy = new UltimataFactory;
	Ship* ship = factoy->createShip();
	string info = ship->getProperty();
	cout << info << endl;

	delete ship;
	delete factoy;
	return 0;
}