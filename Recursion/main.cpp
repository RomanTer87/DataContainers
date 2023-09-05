#include<iostream>
using namespace std;

void elevator(int floor);
int Factorial(int n);
double Power(int a, int n);

//#define ELEVATOR
//#define FACTORIAL
//#define POWER

void main()
{
	setlocale(LC_ALL, "");
	int n;
	int a;
#ifdef ELEVATOR
	cout << "Введите номер этажа: "; cin >> n;
	elevator(n);
#endif // ELEVATOR

#ifdef FACTORIAL
	cout << "Введите число для вычисления факториала: "; cin >> n;
	cout << "Факториал числа " << n << " равен: " << Factorial(n) << endl;
#endif // FACTORIAL

#ifdef POWER
	cout << "Введите число: "; cin >> a;
	cout << "Введите степень числа: "; cin >> n;
	cout << "Число " << a << " в степени " << n << " равно: " << Power(a, n) << endl;
#endif // POWER

}
void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже\n";
	elevator(floor-1);
}

int Factorial(int n)
{
	if (n == 0) return 1;
	return n * Factorial(n - 1);
}

double Power(int a, int n)
{
	if (a == 1 || a == 0)return a;
	if (n > 1)return a * Power(a, n - 1);
	if (n < 1)return 1 / a * Power(a, n + 1);
	return a;
}
