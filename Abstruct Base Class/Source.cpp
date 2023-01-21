#include <iostream>
using namespace std;

class Vehicle
{
	int speed;
public:
	virtual void move() = 0; // ����� ����������� �����
	                         // "=0" ����������, ��� ������ ����� �� ����� �����������, �.�. �� �� ���������

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
		cout << "������ ���� �� 4 �������";
	}
};


void main()
{
	setlocale(LC_ALL, "");
	Car bmw;
	bmw.move();
	
}