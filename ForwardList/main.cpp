#include <iostream>
using namespace std;
#define tab "\t"
#define delimitr "\n---------------------------------------------------------------\n"
class Element
{
	int Data; // значение элемента
	Element* pNext; // адрес следующего элемента
public:
	/*Element* get_pNext() const
	{
		return pNext;
	}
	int get_Data() const
	{
		return Data;
	}*/
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
class ForwardList
{
	Element* Head; //Голова списка - содержит адрес начального элемента списка
public:
	ForwardList()
	{
		Head = nullptr; // Если список пуст, то его голова указывает на 0
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other)
	{
		cout << "LCopyConstructor:\t" << this << endl;
		// Deep copy:
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//					Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		while (Head)pop_front();
		cout << "LCopyAssignment:\t" << this << endl;
		// Deep copy:
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		return *this;
	}

	//					Adding elemetns;
	void push_front(int Data)
	{
		Head = new Element(Data, Head);
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
	}
	//		Deelete elements:
	void pop_front()
	{
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index-1; i++)if(Temp->pNext)Temp = Temp->pNext;
		//1) создаем новый элемент
		Element* New = new Element(Data);
		// 2)
		New->pNext = Temp->pNext;
		// 3)
		Temp->pNext = New;
	}
	void erase(int Index)
	{
		if (Index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < Index-1; i++)
			if (Temp->pNext)
				Temp = Temp->pNext;
		Element* erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete erased;
	}
	

	//					Methods:

	void print() const
	{
		//Element* Temp = Head; //Temp - это итератор
		//// Итератор – это указатель, при помощи которого можно получить доступ к элементам структуры данных
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;//Переход на следующий элемент
		//}
		//cout << endl;
		cout << "Head: " << Head << endl;
		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
};


void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	cout << delimitr << endl;
	//list.push_back(123);
	list.print();
	
	/*int value;
	int index;
	cout << "Введите индекс элемента "; cin >> index;
	cout << "Введите значение элемента "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "Введите индекс элемента "; cin >> index;
	list.erase(index);
	list.print();*/

	//ForwardList list2 = list;
	ForwardList list2;
	list2 = list;		// CopyAssignment
	list2.print();
}