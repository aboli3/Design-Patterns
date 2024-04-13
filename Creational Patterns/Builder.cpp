#include<iostream>
using namespace std;
//main dish
class Entree
{
protected:
	char entree[10];
public:
	const char* getEntree()
	{
		return entree;
	}
};
class Burger :public Entree
{
public:
	Burger()
	{
		std::cout << "macD buger \n";
		strcpy_s(entree, "hambuger");
	}
};
class Hotdog :public Entree
{
public:
	Hotdog()
	{
		std::cout << "its a hotDog \n";
		strcpy_s(entree, "hotDog");
	}
};
////side
class Side
{
protected:
	char _side[10];
public:
	char* getSide()
	{
		return _side;
	}
};

class Fries :public Side
{
public:
	Fries()
	{
		std::cout << "its Fries \n";
		strcpy_s(_side, "fries");
	}
};
class Salad :public Side
{
public:
	Salad()
	{
		std::cout << "its salad \n";
		strcpy_s(_side, "salad");
	}
};

class Drink
{
protected:
	char _drink[10];
public:
	Drink()
	{
		std::cout << "its Dring \n";
		strcpy_s(_drink, "soda");
	}
	char *getDrink()
	{
		return _drink;
	}
};

class MealCombo
{
private:
	Entree* entree;
	Side* side;
	Drink* drink;
	char _bag[100];
public:
	MealCombo(const char* type)
	{
		sprintf_s(_bag, "\n %s meal combo:", type);
	}
	void setEntree(Entree* e)
	{
		entree = e;
	}
	void setSide(Side* s) {
		side = s;
	}
	void setDrink(Drink* d) {
		drink = d;
	}
	const char* openMealBag() {
		sprintf_s(_bag, "%s %s, %s, %s", _bag, entree->getEntree(), side->getSide(), drink->getDrink());
		return _bag;
	}

};
//Builder
class MealBuilder
{
protected:
	MealCombo* meal;
public:
	virtual void cookEntree() {};
	virtual void cookSide() {};
	virtual void fillDrink() {};
	MealCombo* getMeal() {
		return meal;
	}
};
class BurgerMeal :public MealBuilder
{
public:
	BurgerMeal() {
		meal = new MealCombo("Burger");
	}
	void cookEntree() {
		Burger* buger = new Burger;
		meal->setEntree(buger);
	}
	void cookSide() {
		Fries* fries = new Fries;
		meal->setSide(fries);
	}
	void fillDrink() {
		Drink* drink = new Drink;
		meal->setDrink(drink);
	}
};
class HotdogMeal : public MealBuilder
{
public:
	HotdogMeal()
	{
		meal = new MealCombo("Hotdog");
	}
	void cookEntree()
	{
		Hotdog *hotdog = new Hotdog;
		meal->setEntree(hotdog);
	}
	void cookSide()
	{
		Salad *caesar = new Salad;
		meal->setSide(caesar);
	}
	void fillDrink()
	{
		Drink *drink = new Drink;
		meal->setDrink(drink);
	}
};
int main()
{
	MealBuilder* cook = new MealBuilder;
	MealCombo* meal;
	int choice;
	cout << "Select a meal: " << endl;
	cout << "1: Hamburger Meal" << endl;
	cout << "2: Hotdog Meal" << endl;
	cout << "Selection: ";
	cin >> choice;
	cout << endl;
	switch (choice)
	{
	case 1:
		cook = new BurgerMeal;
		break;
	case 2:
		cook = new HotdogMeal;
		break;
	default:
		cout << "Invalid Selection" << endl;
		cook = NULL;
		break;
	}
	cout << "Making selected meal" << endl;

	cook->cookEntree();
	cook->cookSide();
	cook->fillDrink();
	meal = cook->getMeal();
	std::cout << meal->openMealBag() << "\n";
}
