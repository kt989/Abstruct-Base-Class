#include <iostream>
using namespace std;

class Vehicle
{
	int speed;
public:
	virtual void move() = 0; // „исто виртуальный метод
	                         // "=0" показывает, что данный метод не имеет определени€, т.е. он не определен

};

class GroundVehicle : public Vehicle
{

};

class AirVehicle : public Vehicle
{
	int height;
public:
	virtual void take_off()=0;
};

class Car : public GroundVehicle
{
public:
	void move()
	{
		cout << "ћашина едет на 4 колесах";
	}
};


void main()
{
	setlocale(LC_ALL, "");
	Car bmw;
	bmw.move();
	
}