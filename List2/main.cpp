#include"List.h"
#include"List.cpp"

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размера списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	cout << delimiter << endl;
	list.reverse_print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << delimiter << endl;
	list.reverse_print();

#endif // BASE_CHECK

	List<int> list1 = { 3,5,8,13,21 };
	//list1.print();
	for (int i : list1)cout << i << tab; cout << endl;
	/*for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;*/

	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		(*it) *= 10;
	}
	List<int> list2 = { 34,55,89 };
	for (int i : list2)cout << i << tab; cout << endl;

	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

	List<double> d_list1 = { 2.7, 3.14, 5.1 };
	List<double> d_list2 = { 4.4,8.3 };
	List<double> d_list3 = d_list1 + d_list2;
	for (double i : d_list1) cout << i << tab; cout << endl;
	for (double i : d_list2) cout << i << tab; cout << endl;
	for (double i : d_list3) cout << i << tab; cout << endl;
}