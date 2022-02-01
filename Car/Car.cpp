#include<iostream>
using namespace std;

#define MIN_TANK_VOLUME 40
#define MAX_TANK_VOLUME 80
#define MIN_ENGINE_CONSUMPTION 4
#define MAX_ENGINE_CONSUMPTION 25

class Tank
{
	const unsigned int VOLUME;   //Объём бака
	double fuel_level;           //Уровень топлива
public:
	const unsigned int get_VOLUME()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	double fill(double fuel)
	{
		if (fuel_level + fuel < 0)return fuel_level = 0;
		if (fuel_level + fuel > VOLUME)return fuel_level = VOLUME;
		//if (fuel_level + fuel >= 0 && fuel_level + fuel <= VOLUME)fuel_level += fuel;
		else return fuel_level += fuel;
	}
	double give_fuel(double fuel)
	{
		fuel_level -= fuel;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}
	Tank(unsigned int volume)
		:VOLUME(volume >= MIN_TANK_VOLUME && volume <= MAX_TANK_VOLUME ? volume : MAX_TANK_VOLUME), 
		fuel_level(0)
	{
		cout << "Tank is ready\t" <<this << endl;
	}
	~Tank()
	{
		cout << "Tank is gone\t" << this << endl;
	}
	void info()const
	{
		cout << "Tank volume:\t" << VOLUME << endl;
		cout << "Fuel level:\t" << fuel_level << endl;
	}
};

class Engine
{
	double consumption;              //Расход топлива
	double consumption_per_second;   //Расход топлива в секунду
	bool is_started;                 //Старт/стоп
public:
	double get_consumption()const
	{
		return consumption;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	bool started()const
	{
		return is_started;
	}
	bool start()
	{
		return is_started = true;
	}
	bool stop()
	{
		return is_started = false;
	}
	void set_consumption(double consumption)
	{
		if (consumption >= MIN_ENGINE_CONSUMPTION && consumption <= MAX_ENGINE_CONSUMPTION)
			this->consumption = consumption;
		else
			this->consumption = MAX_ENGINE_CONSUMPTION / 2;
		consumption_per_second = consumption * .3e-4;
	}
	explicit Engine(double consumption)
	{
		set_consumption(consumption);
		is_started = false;
		cout << "Engine is ready:\t" << this << endl;
	}
	~Engine()
	{
		cout << "Engine is gone:\t" << this << endl;
	}
	void info()const
	{
		cout << "Consumption:\t" << consumption << endl;
		cout << "Consumption per second:\t" << consumption_per_second << endl;
		cout << "Engine is " << (is_started ? "started" : "stopped") << endl;
	}
};

class Car
{
	Tank car_tank;
	Engine car_engine;
public:
	Car(double fuel_level, double consumption):car_engine(consumption), car_tank(fuel_level)
	{
		this->car_tank.fill(fuel_level);
		this->car_engine.set_consumption(consumption);
		cout << "Car is ready:\t" << this << endl;
	}
	~Car()
	{
		cout << "Car is gone:\t" << this << endl;
	}
	void Launch_car()
	{
		if (car_tank.get_fuel_level() > 0)
		{
			car_engine.start();
			do
			{
				car_tank.give_fuel(car_engine.get_consumption_per_second());
			} while (car_tank.get_fuel_level()!=0);
		}
		else car_engine.stop();
	}
	void Car_info()
	{
		car_tank.info();
		car_engine.info();
	}
};




//#define TANK_CHECK
//#define ENGINE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef TANK_CHECK
	Tank tank(120);
	tank.info();
	while (true)
	{
		int fuel;
		cout << "Введите объём: "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	}
#endif // TANK_CHECK

#ifdef ENGINE_CHECK
	Engine engine(9);
	engine.info();
#endif // ENGINE_CHECK
	
	Car BMW_e39(60, 10);
	BMW_e39.Launch_car();
	BMW_e39.Car_info();
}