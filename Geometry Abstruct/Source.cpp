#define _USE_MATH_DEFINES
#include <iostream>
#include <windows.h>
#include<cmath>
using namespace std;

namespace Geometry
{
	enum Color
	{
		red = 0x000000FF,
	    green = 0x0000FF00,
		blue =0x00FF0000,
		yellow = 0x0000FFFF,

		console_default = 0x07, //Hex-код цвета, первая цифра цвет фона, вторая - цвет текста
		console_red = 0xCC,
		console_green = 0xAA,
		console_blue = 0x99,
		console_yellow = 0xEE,
	};
	/*
	-----------------------------------------------------------
	enum (enumeration) - это перечисление.
	Перечисление - это набор именованных констант типа Int
	-----------------------------------------------------------
	*/

	class Shape //абстрактный базовый класс Геометрических фигур
	{
	protected:
		static const int MIN_START_X = 10;
		static const int MAX_START_X = 800;
		static const int MIN_START_Y = 10;
		static const int MAX_START_Y = 500;
		static const int MIN_LINE_WIDTH = 5;
		static const int MAX_LINE_WIDTH = 25;
		static const int MIN_LENGTH = 15;
		static const int MAX_LENGTH = 500;
		static const int MIN_WIDTH = 15;
		static const int MAX_WIDTH = 500;


	
		Color color;
		int start_x;
		int start_y;
		int line_width;
	public:
		Shape(int start_x, int start_y, int line_width, Color color) :color(color) 
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		void set_start_x(int start_x)
		{
			if (start_x < MIN_START_X)start_x = MIN_START_X;
			if (start_x > MAX_START_X)start_x = MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(int start_y)
		{
			if (start_y < MIN_START_Y)start_y= MIN_START_Y;
			if (start_y > MAX_START_Y)start_y = MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(int line_width)
		{
			if (line_width < MIN_LINE_WIDTH)start_x = MIN_LINE_WIDTH;
			if (line_width > MAX_LINE_WIDTH)start_x = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}

		virtual double get_area() const = 0;
		virtual double get_perimeter() const = 0;
		virtual void draw() const = 0;

		virtual void info() const
		{
			cout << "Площадь: " << get_area() << endl;
			cout << "Периметр: " << get_perimeter() << endl<<endl;
			draw();
		}
	};

	class Parallelogram:public Shape /// Олег, сделала прямоугольник подклассом параллелограмма, а квадрат подклас прямоугольника
		// осталась проблема с рисованием фигур, выводит через раз, и как-то рандомно (то круг выведет, то треугольник, то куски прямоугольника и т.п.),
		//не понимаю почему
	{
		double length;
		double width;
		double angle;
	public:
		double get_width() const
		{
			return width;
		}
		double get_length () const
		{
			return length;
		}
		double get_angle() const
		{
			return angle;
		}
		void set_width(double width)
		{
			if (width < MIN_WIDTH) width = MIN_WIDTH;
			if (width > MAX_WIDTH) width = MAX_WIDTH;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length < MIN_LENGTH) length = MIN_LENGTH;
			if (length > MAX_LENGTH) length = MAX_LENGTH;
			this->length = length;
		}
		void set_angle(double angle)
		{
			if (angle < 10) angle = 10;
			if (angle > 150) angle = 150;
			angle *= M_PI / 180;
			this->angle = angle;
		}
		// Конструктор
		Parallelogram(double length, double width, double angle, int start_x, int start_y, int line_width, Color color) :Shape(start_x, start_y, line_width, color)
		{
			set_length(length);
			set_width(width);
			set_angle(angle);
		}
		~Parallelogram(){}
		double get_area() const
		{
			return length * width * sin(angle);
		}
		double get_perimeter() const
		{
			return (length + width) * 2;
		}
		void draw() const
		{
			/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //подключаем Обработчик консоли
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < length; i++)
			{
				for (int j = 0; j < width; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
			*/
			HWND hwnd = GetConsoleWindow(); //получаем окно консоли
			HDC hdc = GetDC(hwnd); //получаем контекст устройства для окна консоли
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//выбираем чем будем рисовать pen - карандаш - рисует линию
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // Brush - кисть - рисует заливку замкнутой фигуры
			SelectObject(hdc, hPen); //выбираем чем (hPen) и на чем (hdc) будем рисовать
			SelectObject(hdc, hBrush);

			CONST POINT vertex[] =
			{
				{start_x, start_y},
				{start_x, start_y + length},
				{start_x + width, start_y + length}, 
				{start_x+width, start_y}
			};

			::Polygon(hdc, vertex, 4);

			DeleteObject(hBrush);
			DeleteObject(hPen); // удаляем объект hPen
			ReleaseDC(hwnd, hdc); //освобождаем контекст устройства ОБЯЗАТЕЛЬНО

		}
		void info() const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина: " << length << endl;
			cout << "Ширина: " << width << endl;
			cout << "Угол: " << angle << endl;
			Shape::info();

		}

	};

	class Rectangle :public Parallelogram
	{
	public:

		Rectangle(double length, double width, double angle, int start_x, int start_y, int line_width, Color color) :Parallelogram(length, width, angle, start_x, start_y, line_width, color)
		{
			set_length(length);
			set_width(width);
		}
			void info() const
			{
				cout << typeid(*this).name() << endl;
				cout << "Длина: " << get_length() << endl;
				cout << "Ширина: " << get_width() << endl;
				Shape::info();
			}
		
		~Rectangle() {}
		
	};

	class Square : public Rectangle
	{
	public:
		Square(double side, double angle, int start_x, int start_y, int line_width, Color color): Rectangle(side, side, angle, start_x, start_y, line_width, color){}
		void info() const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << get_length() << endl;
			Shape::info();
		}
		~Square(){}
	};

	class Circle : public Shape
	{
		static const int MIN_RADIUS = 15;
		static const int MAX_RADIUS = 500;
		double radius;
	public:
		double get_radius() const
		{
			return radius;
		}
		void  set_radius(double radius)
		{
			if (radius < MIN_RADIUS) radius = MIN_RADIUS;
			if (radius > MAX_RADIUS) radius = MAX_RADIUS;
			this->radius = radius;
		}
		Circle(double radius,  int start_x, int start_y, int line_width, Color color)  
			:Shape(start_x, start_y, line_width, color)
		{
			set_radius(radius);
		}
		~Circle() {}
		double get_area() const
		{
			return M_PI * radius * radius;
		}

		double get_perimeter() const
		{
			return 2 * M_PI * radius;
		}
		void draw() const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color); // Solid - означает сплошную заливку/линию без текстуры
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, 300, 100, 400, 200);

			DeleteObject(hBrush);
			DeleteObject(hPen);	
			ReleaseDC(hwnd, hdc);
		}
		void info() const
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << radius << endl;
			Shape::info();
		}
	};

class Triangle : public Shape
{
public:
	virtual double get_height() const = 0;
	Triangle(int start_x, int start_y, int line_width, Color color)
		:Shape(start_x, start_y, line_width, color){}
	~Triangle(){}
	void info() const
	{
		cout << "Высота треугольника: " << get_height() << endl;
		Shape::info();
	}
};

class IsoscalesTriangle : public Triangle //равнобедренный треугольник
{
	double base; //основание
	double side; // длина стороны
public:
	double get_base() const
	{
		return base;
	}
	double get_side() const
	{
		return side;
	}
	void set_base(double base)
	{
		if (base < MIN_LENGTH)base = MIN_LENGTH;
		if (base > MAX_LENGTH)base = MAX_LENGTH;
		this->base = base;
	}
	void set_side(double side)
	{
		if (side < MIN_LENGTH)side = MIN_LENGTH;
		if (side > MAX_LENGTH)side = MAX_LENGTH;
		this->side = side;
	}
	IsoscalesTriangle(double base, double side, int start_x, int start_y, int line_width, Color color)
		:Triangle(start_x, start_y, line_width, color)
	{
		set_base(base);
		set_side(side);
	}
	~IsoscalesTriangle(){}

	double get_height() const
	{
		return sqrt(pow(side, 2) - pow(base / 2, 2));
	}
	double get_area() const
	{
		return base * get_height() / 2;
	}
	double  get_perimeter() const
	{
		return base + side * 2;
	}
	void draw()const
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);
		HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		HBRUSH hBrush = CreateSolidBrush(color);
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		CONST POINT vertex[] =
		{
			{start_x, start_y + side},
			{start_x + base, start_y + side},
			{start_x + base / 2, start_y + side - get_height()}
		};

		::Polygon(hdc, vertex, 3);

		DeleteObject(hBrush);
		DeleteObject(hPen);

		ReleaseDC(hwnd, hdc);
	}
	void info() const
	{
		cout << typeid(*this).name() << endl;
		cout << "Основание треугольника: " << base << endl;
		cout << "Длина стороны: " << side << endl;
		Triangle::info();

	}
};

}

void main()
{
	setlocale(LC_ALL, "");
	Geometry::Rectangle rect(70, 350, 90, 100, 100, 15, Geometry::Color::red);
	/*cout << "Длина прямоугольника: " << rect.get_length()<<endl;
	cout << "Ширина прямоугольника: " << rect.get_width()<<endl;
	cout << "Площадь прямоугольника: " << rect.get_area() << endl;
	cout << "Периметр прямоугольника: " << rect.get_perimeter() << endl;
	rect.draw();*/
	rect.info();

	Geometry::Parallelogram parallel (30, 40, 30, 300, 700, 15, Geometry::Color::blue);
	parallel.info();

	Geometry::Square square(8, 90, 500, 200, 25, Geometry::Color::red);
	square.info();


	Geometry::Circle circle(50, 800, 700, 5, Geometry::Color::yellow);
	circle.info();


	Geometry::IsoscalesTriangle isoscales(50, 37, 750, 250, 5, Geometry::Color::green);
	isoscales.info();

}