#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <clocale>

using namespace std;

class Component abstract
{
protected:
	string name;
	int price;
public: 

	Component(string name,int price = 0)
	{
		this->name = name;
		this->price = price;
	}

	virtual  void Add(Component *c) abstract;
	virtual  void Remove(Component *c) abstract;
	virtual  void Display(int depth) abstract;
	virtual  int GetPrice() abstract;
};

class Composite : public Component
{
	vector<Component*> components;

public:
	Composite(string name,int price = 0):Component(name, price) {}

	void Add(Component * component) override
	{
		components.push_back(component);
	}

	void Remove(Component *component) override
	{
		auto iter = find(components.begin(), components.end(), component);
		components.erase(iter);
	}

	void Display(int depth) override
	{
		string s(depth, '-');
		cout << s + name << " (" << GetPrice() << ")" << endl;

		for(Component *component : components)
		{
			component->Display(depth + 2);
		}
	}

	int GetPrice() override 
	{
		int total = price;

		for (Component* component : components)
		{
			total += component->GetPrice();
		}

		return total;
	}
};


class Leaf : public Component
{
public:
	Leaf(string name, int price = 0): Component(name, price) {}

	void Add(Component *c) override
	{
		cout << "Cannot add to a leaf\n";
	}

	void Remove(Component *c) override
	{
		cout << "Cannot remove from a leaf\n";
	}

	void Display(int depth) override
	{
		string s(depth, '-');
		cout << s + name << " (" << GetPrice() << ")" << endl;
	}

	int GetPrice() override 
	{
		return price;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	Component* office = new Composite("����",0);

	Component* reception = new Composite("��������", 500);

	reception->Add(new Leaf("����� � ������ �����", 200));
	reception->Add(new Leaf("���������� ������", 100));
	reception->Add(new Leaf("������ �����", 300));

	Component* secretaryDesk = new Composite("���� ���������", 250);

	secretaryDesk->Add(new Leaf("��������� � ������� ������� HDD", 1500));
	secretaryDesk->Add(new Leaf("������� ��������������", 100));
	reception->Add(secretaryDesk);
	reception->Add(new Leaf("����� � �����", 150));

	Component* auditorium1 = new Composite("��������� 1", 1500);

	auditorium1->Add(new Leaf("10 ������", 1000));
	auditorium1->Add(new Leaf("�����", 500));

	Component* teacherDesk = new Composite("���� �������", 300);

	teacherDesk->Add(new Leaf("���������", 1500));
	auditorium1->Add(teacherDesk);
	auditorium1->Add(new Leaf("������� ������� �����������", 200));

	Component* auditorium2 = new Composite("��������� 2", 2000);

	auditorium2->Add(new Leaf("20 ������ � �����", 2000));
	auditorium2->Add(new Leaf("�����", 500));
	auditorium2->Add(new Leaf("������ �����", 300));

	Component* computerRoom = new Composite("������������ ���������", 5000);
	Component* computerDesks = new Composite("10 ������������ ������", 2000);

	for (int i = 0; i < 10; i++) 
	{
		Component* computer = new Composite("���������", 1500);
		computer->Add(new Leaf("��������� 2.2���", 500));
		computer->Add(new Leaf("��������� 80��", 250));
		computer->Add(new Leaf("��� 1024��", 100));
		computerDesks->Add(computer);
	}

	computerRoom->Add(computerDesks);
	computerRoom->Add(new Leaf("����� � ���������", 150));

	Component* canteen = new Composite("��������", 1000);

	canteen->Add(new Leaf("�������� �������", 800));

	Component* diningTable = new Composite("���� � 4 ��������", 400);

	canteen->Add(diningTable);
	canteen->Add(new Leaf("�����������", 1500));
	canteen->Add(new Leaf("����������", 300));

	office->Add(reception);
	office->Add(auditorium1);
	office->Add(auditorium2);
	office->Add(computerRoom);
	office->Add(canteen);

	office->Display(1);
	cout << "����� ���������: " << office->GetPrice() << " ���." << endl;


	delete office;

	system("pause");
}


