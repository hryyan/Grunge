// 函数指针复习
// #include <string>
// #include <stdio.h>
// using std::string;

// void getbool(int x)
// {
//    	printf ("%d\n", x);
// }

// int main()
// {
// 	//使用typedef定义一个类型
// 	typedef void (*pdef)(int);
// 	pdef pf1 = &getbool;

// 	//直接获得一个函数指针
// 	void (*pf2)(int);
// 	pf2 = &getbool;
	
// 	pf1(5);
// 	pf2(4);
// 	return 0;
// }

// 策略模式(Strategy pattern)
// 对算法的封装！
// #include <stdio.h>
// #include <memory>
// using std::auto_ptr;

// class Strategy
// {
// public:
// 	Strategy(){};
// 	virtual ~Strategy(){};
// 	virtual void operate(){printf("Base operate!\n");};
// };

// class Strategy_1 : public Strategy
// {
// public:
// 	Strategy_1(){};
// 	virtual ~Strategy_1(){};
// 	virtual void operate(){printf("Strategy1\n");};
// };

// class Strategy_2 : public Strategy
// {
// public:
// 	Strategy_2(){};
// 	virtual ~Strategy_2(){};
// 	virtual void operate(){printf("Strategy2\n");};
// };

// class Context
// {
// public:
// 	Context(auto_ptr<Strategy> str){strategy = str;};
// 	~Context(){};//防止内存泄露
// 	void op(){strategy->operate();};
// private:
// 	auto_ptr<Strategy> strategy;
// };

// int main(int argc, char const *argv[])
// {
// 	Context* s1 = new Context(auto_ptr<Strategy>(new Strategy_1()));
// 	Context* s2 = new Context(auto_ptr<Strategy>(new Strategy_2()));

// 	s1->op();
// 	s2->op();

// 	//使用指针指向栈，然后析构函数删除该指针，造成错误
// 	// Strategy* s;
// 	// Strategy_1 a;
// 	// Context* s3 = new Context(s);
// 	// s3->op();

// 	//改用智能指针后
// 	// Strategy* s;
// 	// Strategy_1 a;
// 	// s = &a;
// 	// auto_ptr<Strategy> b(s);
// 	// Context* s3 = new Context(b);
// 	// s3->op();

// 	return 0;
// }

// C++中的函数指针必须有参数类型和返回类型，对于策略的限制太大。
// 策略模式(Strategy pattern) Another implement

// #include <stdio.h>

// typedef void (*pf)(void);

// void strategy1()
// {
// 	printf("strategy1!\n");
// }

// void strategy2()
// {
// 	printf("strategy2!\n");
// }

// int main(int argc, char const *argv[])
// {
// 	pf p1 = strategy1;
// 	pf p2 = strategy2;

// 	p1();
// 	p2();
// 	return 0;
// }


// 代理模式(proxy pattern) 
// 对访问的控制！

// #include <stdio.h>

// class Girl
// {
// public:
// 	Girl(){};
// 	~Girl();
// 	void kiss(){printf("Kiss!\n");};
// 	void hug(){printf("Hug!\n");};
// };

// class Wrap
// {
// public:
// 	Wrap(Girl* g){girl = g;};
// 	~Wrap();
// 	void kiss(){girl->kiss();};
// 	void hug(){girl->hug();};

// private:
// 	Girl* girl;
// };

// int main(int argc, char const *argv[])
// {
// 	Wrap* w = new Wrap(new Girl());
// 	w->kiss();
// 	w->hug();
// 	return 0;
// }

// 单例模式(Singleton Pattern)
// #include <stdio.h>

// class Singleton
// {
// private:
// 	Singleton(){};
// 	static Singleton* instance;

// public:
// 	static Singleton* getInstance(){if(instance == NULL) instance = new Singleton(); return instance;};
// 	static void printinfo(){printf("This is Singleton\n");};
// 	virtual ~Singleton(){};
// };

// Singleton* Singleton::instance = new Singleton();

// int main(int argc, char const *argv[])
// {
// 	Singleton* a = Singleton::getInstance();
// 	Singleton* b = Singleton::getInstance();
// 	Singleton* c = Singleton::getInstance();
// 	a->printinfo();
// 	b->printinfo();
// 	c->printinfo();
// 	return 0;
// }

// 单例模式(Singleton Pattern) 模板实现
// #include <iostream>
// using std::cout;
// using std::endl;

// template <typename T>
// class Singleton
// {
// public:
// 	static T* instance()
// 	{
// 		if (!t_)
// 			t_ = new T();
// 		return t_;
// 	}
// private:
// 	Singleton();
// 	static T* t_;
// };

// template <typename T>
// T* Singleton<T>::t_ = NULL;

// class Stu
// {
// public:
// 	void print()
// 	{
// 		cout << "Example" << endl;
// 	}
// };

// int main(int argc, char const *argv[])
// {
// 	Stu *s = Singleton<Stu>::instance();
// 	Stu *s2 = Singleton<Stu>::instance();
// 	if(s == s2)
// 		cout << "Equal" << endl;
// 	return 0;
// }


// 多例模式(Multition Pattern)
// #include <stdio.h>
// #include <vector>
// #include <stdlib.h>
// #include <windows.h>
// #include <time.h>

// class Multition
// {
// private:
// 	Multition(){};
// 	static std::vector<Multition*> v_instance;
// 	static int MaxNumOfInstance;

// public:
// 	static Multition* getInstance()
// 	{
// 		if (MaxNumOfInstance == v_instance.size())
// 		{
// 			srand((int)time(0));
// 			int n = rand() % 2;
// 			printf("Return Instance %d\n", n);
// 			return v_instance[n];
// 		}
// 		else
// 		{
// 			Multition* instance = new Multition();
// 			int n = v_instance.size();
// 			v_instance.push_back(instance);

// 			printf("Create Instance %d\n", n);
// 			return instance;
// 		}
// 	};
// 	virtual ~Multition(){};
// };

// int Multition::MaxNumOfInstance = 2;
// std::vector<Multition*> Multition::v_instance;

// int main(int argc, char const *argv[])
// {
// 	for (int i = 0; i < 10; ++i)
// 	{
// 		Multition* a = Multition::getInstance();
// 		Sleep(150);
// 	}
// 	return 0;
// }

// 简单工厂模式(Factory Pattern)
// 增加新的产品时，就需要修改工厂类。

// #include <stdio.h>

// class Man
// 	{
// public:
// 	Man(){};
// 	virtual ~Man(){};
// 	virtual void smile(){};
// };

// class WhiteMan : public Man
// {
// public:
// 	WhiteMan(){};
// 	~WhiteMan(){};

// 	void smile(){printf("WhiteMan smile!\n");};
// };

// class BlackMan : public Man
// {
// public:
// 	BlackMan(){};
// 	~BlackMan(){};

// 	void smile(){printf("BlackMan smile!\n");};
// };

// class YellowMan : public Man
// {
// public:
// 	YellowMan(){};
// 	~YellowMan(){};

// 	void smile(){printf("YellowMan smile!\n");};
// };

// enum MAN {WHITEMAN, BLACKMAN, YELLOWMAN};

// class Factory
// {
// public:
// 	Factory(){};
// 	~Factory(){};

// 	Man* createMan(enum MAN m)
// 	{
// 		if (m == WHITEMAN)
// 			return new WhiteMan();
// 		else if (m == BLACKMAN)
// 			return new BlackMan();
// 		else if (m == YELLOWMAN)
// 			return new YellowMan();
// 		else
// 			return NULL;
// 	};
// };

// int main(int argc, char const *argv[])
// {
// 	Factory* factory = new Factory();
// 	Man* man_1 = factory->createMan(WHITEMAN);
// 	Man* man_2 = factory->createMan(BLACKMAN);
// 	Man* man_3 = factory->createMan(YELLOWMAN);

// 	man_1->smile();
// 	man_2->smile();
// 	man_3->smile();
// 	return 0;
// }

// 工厂方法模式(Factory Method Pattern)
// 定义一个用于创建对象的接口，让子类决定实例化哪一个类。
// 工厂方法模式可以使一个类的实例化延迟到其子类

// #include <stdio.h>

// class Mankind
// {
// public:
// 	Mankind(){};
// 	virtual ~Mankind(){};

// 	virtual void smile() = 0;
// };

// class Male : public Mankind
// {
// public:
// 	Male(){};
// 	~Male(){};
// 	void smile(){printf("Male smile!\n");};
// };

// class Female : public Mankind
// {
// public:
// 	Female(){};
// 	~Female(){};
// 	void smile(){printf("Female smile!\n");};
// };

// class Factory
// {
// public:
// 	Factory(){};
// 	virtual ~Factory(){};

// 	virtual Mankind* create() = 0;
// };

// class MaleFactory : public Factory
// {
// public:
// 	MaleFactory(){};
// 	~MaleFactory(){};
// 	Male* create(){return new Male();};
// };

// class FemaleFactory : public Factory
// {
// public:
// 	FemaleFactory(){};
// 	~FemaleFactory(){};
// 	Female* create(){return new Female();};
// };


// int main(int argc, char const *argv[])
// {
// 	FemaleFactory* ff = new FemaleFactory();
// 	Female* f = ff->create();
// 	f->smile();

// 	MaleFactory* mf = new MaleFactory();
// 	Male* m	= mf->create();
// 	m->smile();
// 	return 0;
// }

// 抽象工厂模式(Abstract Factory Pattern)
// 提供一个创建一系列相关或相互依赖的接口，而无需指定他们的类

// #include <iostream>
// using std::cout;
// using std::endl;

// class Mankind
// {
// public:
// 	Mankind(){};
// 	virtual ~Mankind(){};

// 	virtual void smile() = 0;
// };

// class WhiteMale : public Mankind
// {
// public:
// 	WhiteMale(){};
// 	~WhiteMale(){};

// 	void smile(){cout << "WhiteMale smile!" << endl;};
// };

// class WhiteFemale : public Mankind
// {
// public:
// 	WhiteFemale(){};
// 	~WhiteFemale(){};

// 	void smile(){cout << "WhiteFemale smile!" << endl;};
// };

// class BlackMale : public Mankind
// {
// public:
// 	BlackMale(){};
// 	~BlackMale(){};

// 	void smile(){cout << "BlackMale smile!" << endl;};
// };

// class BlackFemale : public Mankind
// {
// public:
// 	BlackFemale(){};
// 	~BlackFemale(){};

// 	void smile(){cout << "BlackFemale smile!" << endl;};
// };

// class Factory
// {
// public:
// 	Factory(){};
// 	virtual ~Factory(){};

// 	virtual Mankind* createWhite() = 0;
// 	virtual Mankind* createBlack() = 0;
// };

// class MaleFactory : public Factory
// {
// public:
// 	MaleFactory(){};
// 	~MaleFactory(){};

// 	WhiteMale* createWhite(){return new WhiteMale();};
// 	BlackMale* createBlack(){return new BlackMale();};
// };

// class FemaleFactory : public Factory
// {
// public:
// 	FemaleFactory(){};
// 	~FemaleFactory(){};

// 	WhiteFemale* createWhite(){return new WhiteFemale();};
// 	BlackFemale* createBlack(){return new BlackFemale();};
// };

// int main(int argc, char const *argv[])
// {
// 	MaleFactory* mf = new MaleFactory();
// 	FemaleFactory* ff = new FemaleFactory();
// 	WhiteMale* wm = mf->createWhite();
// 	BlackMale* bm = mf->createBlack();
// 	WhiteFemale* wf = ff->createWhite();
// 	BlackFemale* bf = ff->createBlack();
// 	wm->smile();
// 	bm->smile();
// 	wf->smile();
// 	bf->smile();

// 	return 0;
// }