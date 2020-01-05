#include "pch.h"
#include <iostream>
// бинарное дерево
using namespace std;

struct Item
{
	int key;
	Item* next_left; //левое плечо
	Item* next_right; //правое плечо
	Item* next_p; //родитель
};

void Add_elem(int m, Item*copy, Item*p, Item*parent)
{
	if (p == NULL)
	{
		p = new Item;
		p->next_left = 0;
		p->next_right = 0;
		p->key = m;
		p->next_p = parent;
		
		//связываем элементы созданного и родителя
		if (m < parent->key)
		{
			parent->next_left = p;
		}
		else
		{
			parent->next_right = p;
		}
		return;
	}
	if (m < p->key)
	{
		Add_elem(m, copy, p->next_left, p); // (7, начало дерева, текущий элемент, указатель на родителя(предыдущий))
	}
	else
	{
		Add_elem(m, copy, p->next_right, p);
	}
}

void show(Item*copy) // вывод в разных порядках
{
	if (copy == NULL)
	{
		return;
	}
	//cout << copy->key << " "; // обход в прямом порядке
	show(copy->next_left);
	cout << copy->key << " "; //симметричный обход
	show(copy->next_right);
	//cout << copy->key << " "; // обход в обратном порядке
}

void func_min(Item *copy)
{
	while (copy->next_left)
	{	
		copy = copy->next_left;
	}
	cout << copy->key << endl;
}

void func_max(Item *copy)
{
	while (copy->next_right)
	{
		copy = copy->next_right;
	}
	cout << copy->key << endl;
}

void f_delete(Item *copy, int a)
{
	if (copy == NULL)
	{
		return;
	}
	
	else if (copy->key == a)
	{
		if (copy->next_p->key < a)
		{
			copy->next_p->next_right = 0;
			delete copy;
		}
		else
		{
			copy->next_p->next_left = 0;
			delete copy;
		}
		return;
		/*Item *per = copy->next_p;
		per->next_right = 0;
		delete (copy);
		//cout << copy->key << endl;
		return;*/
	}
		else
	{
		f_delete(copy->next_left, a);
		f_delete(copy->next_right, a);
	}
	//cout << copy->key << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");

	int mas[9] = { 10,7,9,12,6,14,11,3,4 };

	Item * free = 0; // создаем указатель на корень дерева
	Item *p; // создаем объект текущий
	Item *parent; //указатель на родителя

	p = new Item;
	p->key = mas[0];
	p->next_left = 0;
	p->next_right = 0;
	p->next_p = 0;
	free = p;

	for (int i = 1; i < 9; i++)
	{
		Item *copy = free;
		Add_elem(mas[i], copy, copy, copy); //(7, copy, p, parent)
	}

	//вывод на консоль

	Item *copy = free;
	show(copy);
	cout << "\n";
	func_min(copy);
	cout << "\n";
	func_max(copy);

	f_delete(copy,11);
	show(copy);

	system("pause");
	return 0;
}
