#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int i : il)insert(i, Root);
	}
	~Tree()
	{
		Clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	void Clear()
	{
		Clear(Root);
		Root = nullptr;
	}
	int Count()const
	{
		return Count(Root);
	}
	int Depth()const
	{
		return Depth(Root);
	}
	double Avg()const
	{
		return (double)Sum(Root) / Count(Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	void Clear(Element* Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
	}
	int Depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		return 
			Depth(Root->pLeft) + 1 < Depth(Root->pRight) + 1 ?
			Depth(Root->pRight) + 1 :
			Depth(Root->pLeft)+1;
	}
	int Sum(Element* Root)const
	{
		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	int Count(Element* Root)const
	{
		return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
	}
	

	int minValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
	}
	int maxValue(Element* Root)const 
	{
		if (Root == nullptr)return 0;
		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		/*if (Root->pRight == nullptr) return Root->Data;
		else return maxValue(Root->pRight);*/
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

#define BASE_CHECK
//#define DEPTH_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размера дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	//tree.Clear();
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве:  " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Сумма элементов дерева:\t\t" << tree.Sum() << endl;
	cout << "Количество элементов дерева:\t" << tree.Count() << endl;
	cout << "Среднее-арифметическое элементов дерева: " << tree.Avg() << endl;
	cout << "Глубина дерева: " << tree.Depth() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве:  " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Сумма элементов дерева:\t\t" << u_tree.Sum() << endl;
	cout << "Количество элементов дерева:\t" << u_tree.Count() << endl;
	cout << "Среднее-арифметическое элементов дерева: " << u_tree.Avg() << endl;
	cout << "Глубина дерева: " << u_tree.Depth() << endl;
#endif // BASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50,25,75,16,32,64,90,28 };
	tree.print();
	cout << "Глубина дерева: " << tree.Depth() << endl;
#endif // DEPTH_CHECK


}