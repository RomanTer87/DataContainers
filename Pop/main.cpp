#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
#include"math.h"
//#include<cmath>
using namespace std;

#define delimitr "\n----------------------------------------------------------\n"

namespace Geometry
{
	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,
		console_red = 0xCC, //0x - Hexadecimal 
		console_green = 0xAA,
		console_blue = 0x1,
		console_defuult = 0x07
	};

#define SHAPE_TAKE_PARAMETERS	int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS	start_x, start_y, line_width, color

	class Shape
	{
		static const int MIN_START_X = 10;
		static const int MIN_START_Y = 10;
		static const int MAX_START_X = 500;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 10;
		static const int MAX_LINE_WIDTH = 400;

	protected:
		int start_x;
		int start_y;
		int line_width;
		Color color;
	public:
		Shape(int start_x, int start_y, int line_width, Color color) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}
		int get_start_x() const
		{
			return start_x;
		}
		int get_start_y() const
		{
			return start_y;
		}
		int get_line_width() const
		{
			return line_width;
		}
		void set_start_x(int start_x)
		{
			if (start_x < MIN_START_X) start_x = MIN_START_X;
			if (start_x > MAX_START_X) start_x = MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(int start_y)
		{
			if (start_y < MIN_START_Y) start_y = MIN_START_Y;
			if (start_y > MAX_START_Y) start_y = MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(int line_width)
		{
			if (line_width < MIN_LINE_WIDTH) line_width = MIN_LINE_WIDTH;
			if (line_width > MAX_LINE_WIDTH) line_width = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}

		virtual double get_area()const = 0;
		virtual double get_perimeter() const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			system("PAUSE");
			system("cls");
			draw();
		}
	};

	class Triangle :public Shape
	{
		static const int MIN_SIDE = 20;
		static const int MAX_SIDE = 500;
		double side_one;
		double side_two;
		double side_three;
		double height;
	public:
		double get_side_one() const
		{
			return side_one;
		}
		double get_side_two() const
		{
			return side_two;
		}
		double get_side_three() const
		{
			return side_three;
		}
		double get_height() const
		{
			return (2 * this->get_area()) / max(max(side_one, side_two), side_three);
		}
		void set_side_one(double side_one)
		{
			if (side_one < MIN_SIDE) side_one = MIN_SIDE;
			if (side_one > MAX_SIDE) side_one = MAX_SIDE;
			this->side_one = side_one;
		}
		void set_side_two(double side_two)
		{
			if (side_two < MIN_SIDE) side_two = MIN_SIDE;
			if (side_two > MAX_SIDE) side_two = MAX_SIDE;
			this->side_two = side_two;
		}
		void set_side_three(double side_three)
		{
			if (side_three < MIN_SIDE) side_three = MIN_SIDE;
			if (side_three > MAX_SIDE) side_three = MAX_SIDE;
			this->side_three = side_three;
		}
		Triangle(double side_one, double side_two, double side_three, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			double max_side = max(max(side_one, side_two), side_three);
			double min_side = min(min(side_one, side_two), side_three);
			double three_side = (side_one + side_two + side_three) - (max_side + min_side);
			if (max_side >= (min_side + three_side)) max_side = (min_side + three_side) - 10;
			// В трегольника невозможно чтобы большая сторона была больше или равнялась сумме остальных двух сторон
			set_side_one(max_side);
			set_side_two(min_side);
			set_side_three(three_side);
			//cout << "TConstructor:\t" << this << endl;
		}
		Triangle(double katet_a, double katet_b, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side_two(katet_a);
			set_side_three(katet_b);
			set_side_one(round(sqrt((katet_a * katet_a) + (katet_b * katet_b)) * 10) / 10);
		}
		~Triangle()
		{
			//cout << "TDestructor:\t" << this << endl;
		}
		double get_area() const override
		{
			double pperimetr = this->get_perimeter() / 2;
			return round(sqrt(pperimetr * (pperimetr - side_one) * (pperimetr - side_two) * (pperimetr - side_three)) * 10) / 10;
		}
		double get_perimeter() const override
		{
			return side_one + side_two + side_three;
		}
		void draw() const override
		{
			double a_cattle = round(sqrt((get_side_two() * get_side_two()) - (get_height() * get_height())) * 10) / 10;
			double b_cattle = get_side_one() - a_cattle;
			//cout << base_side << " " << one_side << " " << two_side << " " << a_cattle << " " << b_cattle << " " << this->get_height() << endl;

			// Получаем окно консоли
			HWND hwnd = GetConsoleWindow();
			//2) Создаем контекст устройства
			HDC hdc = GetDC(hwnd);
			//3) Создаем кисть и карандаш
			HPEN hPen = CreatePen(PS_SOLID, get_line_width(), color);
			//4) Кисть заливает цветом фигуру
			HBRUSH hBrush = CreateSolidBrush(color);
			//5) Выбираем объекты - на чем и чем будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//6) Рисуем фигуру с помощью функции многоугольника Polygon

			::POINT triangle[3] = { {get_start_x(), get_start_y()}, {get_start_x() + b_cattle, get_start_y() + get_height()}, {get_start_x() - a_cattle, get_start_y() + get_height()} };
			::Polygon(hdc, triangle, 3);


			DeleteObject(hBrush);
			DeleteObject(hPen);
			DeleteObject(hdc);

		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << (side_one != side_two && side_one != side_three ? "Длинна стороны a:" : "Длинна стороны равностороннего треугольника: ") << get_side_one() << endl;
			if (side_one != side_two)cout << (side_two == side_three ? "Длинна равнобедренной стороны: " : "Длинна стороны b: ") << get_side_two() << endl;
			if (side_two != side_three)cout << "Длинна стороны c: " << get_side_three() << endl;
			Shape::info();
		}
	};
	class Triangle_Equilateral :public Triangle
	{
	public:
		Triangle_Equilateral(double side, SHAPE_TAKE_PARAMETERS) :Triangle(side, side, side, SHAPE_GIVE_PARAMETERS) {}
		~Triangle_Equilateral() {}
	};
	class Triangle_Isosceles :public Triangle
	{
	public:
		Triangle_Isosceles(double side_isos, double base_side, SHAPE_TAKE_PARAMETERS) :Triangle(side_isos, side_isos, base_side, SHAPE_GIVE_PARAMETERS) {}
		~Triangle_Isosceles() {}
	};
	class Triangle_Right :public Triangle
	{
	public:
		double get_hypotenuse() const
		{
			return round((sqrt(get_side_one() * get_side_one() + get_side_two() * get_side_two())) * 10) / 10;
		}
		Triangle_Right(double katet_a, double katet_b, SHAPE_TAKE_PARAMETERS) :Triangle(katet_a, katet_b, SHAPE_GIVE_PARAMETERS) {}
		~Triangle_Right() {}
	};

	class Rectangle :public Shape
	{
		static const int MIN_SIDE = 20;
		static const int MAX_SIDE = 500;
		double long_side;
		double width_side;
	public:
		Rectangle(double long_side, double width_side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_long_side(long_side);
			set_width_side(width_side);
			//cout << "RectangleConstructor:\t" << this << endl;
		}
		double get_long_side() const
		{
			return long_side;
		}
		double get_width_side() const
		{
			return width_side;
		}
		void set_long_side(double long_side)
		{
			if (long_side < MIN_SIDE) long_side = MIN_SIDE;
			if (long_side > MAX_SIDE) long_side = MAX_SIDE;
			this->long_side = long_side;
		}
		void set_width_side(double width_side)
		{
			if (width_side < MIN_SIDE) width_side = MIN_SIDE;
			if (width_side > MAX_SIDE) width_side = MAX_SIDE;
			this->width_side = width_side;
		}
		double get_area() const override
		{
			return long_side * width_side;
		}
		double get_perimeter() const override
		{
			return (long_side + width_side) * 2;
		}
		void draw() const override
		{
			//1) Получаем окно консоли
			HWND hwnd = GetConsoleWindow(); //Получаем окно консоли (Функция GetConsoleWindow() возвращает hwnd окна консоли из текущего потока команд)
			//HWND - Hangler to Window (Обработчик окна)
			// К переменной можно обратится по имени, к окну можно обратится через hwnd
			//2) СОздаем контекст устройства
			HDC hdc = GetDC(hwnd); // СОздаем контекст устройства
			// контекст устройства есть у каждого окна
			// Рисовать можно только на контексте устройства
			// Функция GetDC(hwnd) возращает контекст устройства заданного окна
			//3) Создаем кисть и карандаш
			HPEN hPen = CreatePen(PS_SOLID, get_line_width(), color); //карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color); //Кисть заливает цветом фигуру

			//4) Выбираем чем и на чем будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) Рисуем фигуру
			::Rectangle(hdc, get_start_x(), get_start_y(), get_start_x() + get_long_side(), get_start_y() + get_width_side());

			DeleteObject(hPen);
			DeleteObject(hBrush);
			DeleteObject(hdc);
			/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < width_side; i++)
			{
				for (int j = 0; j < long_side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_defuult);*/
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << (long_side != width_side ? "Длинна стороны a: " : "Длинна стороны квадрата: ") << get_long_side() << endl;
			if (long_side != width_side)cout << "Длинна стороны b: " << get_width_side() << endl;
			Shape::info();
		}
		~Rectangle() {}

	};
	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square() {}
	};

	class Ellipse :public Shape
	{
		static const int MIN_SIZE = 20;
		static const int MAX_SIZE = 500;
		double semiaxis_a;
		double semiaxis_b;
	public:
		double get_semiaxis_a() const
		{
			return semiaxis_a;
		}
		double get_semiaxis_b() const
		{
			return semiaxis_b;
		}
		void set_semiaxis_a(double semiaxis_a)
		{
			this->semiaxis_a = semiaxis_a;
		}
		void set_semiaxis_b(double semiaxis_b)
		{
			this->semiaxis_b = semiaxis_b;
		}
		Ellipse(double semiaxis_a, double semiaxis_b, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			if (semiaxis_a < MIN_SIZE) semiaxis_a = MIN_SIZE;
			if (semiaxis_a > MAX_SIZE) semiaxis_a = MAX_SIZE;
			if (semiaxis_b < MIN_SIZE) semiaxis_b = MIN_SIZE;
			if (semiaxis_b > MAX_SIZE) semiaxis_b = MAX_SIZE;
			set_semiaxis_a(semiaxis_a);
			set_semiaxis_b(semiaxis_b);
			//cout << "EConstructor:\t" << this << endl;
		}
		~Ellipse()
		{
			//cout << "EDestructor:\t" << this << endl;
		}
		double get_area() const override
		{
			return round(M_PI * semiaxis_a * semiaxis_b * 10) / 10;
		}
		double get_perimeter() const override
		{
			return round(2 * M_PI * sqrt((semiaxis_a * semiaxis_a + semiaxis_b * semiaxis_b) / 2) * 10) / 10;
		}
		void draw() const override
		{
			for (int i = 0; i < semiaxis_a * 2; i++) cout << "\n";
			//cout << "Рисуем круг, нажмите на любую клавишу" << endl;
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			//создаём перо (контур)
			HPEN hPen = CreatePen(PS_SOLID, get_line_width(), color); //сплошная линия, толщиной 10 пикселей, цвет - зеленый
			//создаём кисть (заливка)
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);// указываем перо 
			SelectObject(hdc, hBrush);//указываем кисть
			//рисуем эллипс
			::Ellipse(hdc, get_start_x(), get_start_y(), get_start_x() + get_semiaxis_a(), get_start_y() + get_semiaxis_b());

			DeleteObject(hBrush);
			DeleteObject(hPen);
			DeleteObject(hdc);
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << (semiaxis_a != semiaxis_b ? "Радиус элипса а: " : "Радиус круга: ") << get_semiaxis_a() << endl;
			if (semiaxis_a != semiaxis_b)cout << "Радиус элипса b: " << get_semiaxis_b() << endl;
			Shape::info();
		}

	};
	class Circle :public Ellipse
	{
	public:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) : Ellipse(radius, radius, SHAPE_GIVE_PARAMETERS) {}
		~Circle() {}
	};
}
//#define RECTANGLE_MAIN
//#define SQUARE_MAIN
//#define TRIANGLE_MAIN
//#define ELLIPS_MAIN
//#define CIRCLE_MAIN
//#define TRIANGLE_EQUILATERAL
//#define TRIANGLE_ISOSCELES
//#define TRIANGLE_RIGHT

void main()
{
	setlocale(LC_ALL, "");
#ifdef RECTANGLE_MAIN
	//					ПРЯМОУГОЛЬНИК
	Geometry::Rectangle rect(300, 100, 100, 150, 5, Geometry::Color::blue);
	rect.info();
#endif // RECTANGLE_MAIN

#ifdef SQUARE_MAIN
	//					Квадрат
	Geometry::Square square(200, 100, 150, 5, Geometry::Color::red);
	square.info();
#endif // SQUARE_MAIN

#ifdef ELLIPS_MAIN
	//					Элипс
	Geometry::Ellipse ellipse(200, 100, 150, 250, 5, Geometry::Color::green);
	ellipse.info();
#endif // ELLIPS_MAIN

#ifdef CIRCLE_MAIN
	//					Круг
	Geometry::Circle circle(200, 150, 250, 5, Geometry::Color::green);
	circle.info();

#endif // CIRCLE_MAIN

#ifdef TRIANGLE_MAIN
	//					Треугольник
	Geometry::Triangle triangle(100, 180, 150, 600, 150, 5, Geometry::Color::blue);
	triangle.info();
#endif // TRIANGLE_MAIN

#ifdef TRIANGLE_EQUILATERAL
	//					Равносторонний треугольник
	Geometry::Triangle_Equilateral triangle_eq(200, 600, 150, 5, Geometry::Color::red);
	triangle_eq.info();

#endif // TRIANGLE_EQUILATERAL

#ifdef TRIANGLE_ISOSCELES
	//					Равнобедренный треугольник
	Geometry::Triangle_Isosceles triangle_is(200, 300, 600, 150, 5, Geometry::Color::yellow);
	triangle_is.info();
#endif // TRIANGLE_ISOSCELES

#ifdef TRIANGLE_RIGHT
	//					Прямоугольный треугольник по 2 катетам
	Geometry::Triangle_Right triangle_right(100, 150, 600, 150, 5, Geometry::Color::yellow);
	triangle_right.info();
#endif // TRIANGLE_RIGHT

	//			Генерация фигур
	srand(time(0)); // Запуск генерации случайных чисел
	int gener = rand() % 3;
	if (gener == 1)
	{
		Geometry::Triangle triangle(rand() % 480 + 20, rand() % 480 + 20, rand() % 480 + 20, 600, 150, 5, Geometry::Color::blue);
		triangle.info();
	}
	else if (gener == 2)
	{
		Geometry::Rectangle rect(rand() % 480 + 20, rand() % 480 + 20, 100, 150, 5, Geometry::Color::green);
		rect.info();
	}
	else
	{
		Geometry::Ellipse elips(rand() % 300 + 20, rand() % 300 + 20, 150, 250, 5, Geometry::Color::yellow);
		elips.info();
	}

}