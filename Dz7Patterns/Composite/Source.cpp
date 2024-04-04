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

	Component* office = new Composite("Офис",0);

	Component* reception = new Composite("Приемная", 500);

	reception->Add(new Leaf("Декор в теплых тонах", 200));
	reception->Add(new Leaf("Журнальный столик", 100));
	reception->Add(new Leaf("Мягкий диван", 300));

	Component* secretaryDesk = new Composite("Стол секретаря", 250);

	secretaryDesk->Add(new Leaf("Компьютер с большим объемом HDD", 1500));
	secretaryDesk->Add(new Leaf("Офисный инструментарий", 100));
	reception->Add(secretaryDesk);
	reception->Add(new Leaf("Кулер с водой", 150));

	Component* auditorium1 = new Composite("Аудитория 1", 1500);

	auditorium1->Add(new Leaf("10 столов", 1000));
	auditorium1->Add(new Leaf("Доска", 500));

	Component* teacherDesk = new Composite("Стол учителя", 300);

	teacherDesk->Add(new Leaf("Компьютер", 1500));
	auditorium1->Add(teacherDesk);
	auditorium1->Add(new Leaf("Плакаты великих математиков", 200));

	Component* auditorium2 = new Composite("Аудитория 2", 2000);

	auditorium2->Add(new Leaf("20 столов в овале", 2000));
	auditorium2->Add(new Leaf("Доска", 500));
	auditorium2->Add(new Leaf("Мягкий диван", 300));

	Component* computerRoom = new Composite("Компьютерная аудитория", 5000);
	Component* computerDesks = new Composite("10 компьютерных столов", 2000);

	for (int i = 0; i < 10; i++) 
	{
		Component* computer = new Composite("Компьютер", 1500);
		computer->Add(new Leaf("Процессор 2.2ГГц", 500));
		computer->Add(new Leaf("Винчестер 80ГБ", 250));
		computer->Add(new Leaf("ОЗУ 1024МБ", 100));
		computerDesks->Add(computer);
	}

	computerRoom->Add(computerDesks);
	computerRoom->Add(new Leaf("Доска с маркерами", 150));

	Component* canteen = new Composite("Столовая", 1000);

	canteen->Add(new Leaf("Кофейный автомат", 800));

	Component* diningTable = new Composite("Стол с 4 стульями", 400);

	canteen->Add(diningTable);
	canteen->Add(new Leaf("Холодильник", 1500));
	canteen->Add(new Leaf("Умывальник", 300));

	office->Add(reception);
	office->Add(auditorium1);
	office->Add(auditorium2);
	office->Add(computerRoom);
	office->Add(canteen);

	office->Display(1);
	cout << "Общая стоимость: " << office->GetPrice() << " грн." << endl;


	delete office;

	system("pause");
}


