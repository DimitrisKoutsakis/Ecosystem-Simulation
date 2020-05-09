#pragma once
#include "plant.h"
#include "terrain.h"
#include <string>
#include <vector>

using namespace std;

class Animal {
protected:
	string name;
	vector<char> whitelistTiles;
	char token;		//herbivore (H) - carnivore (C)
	bool isAlive, isHungry, inHeat, hibernates, isAdult;
	int size, hungerCount, eatCount, speed, eatenFood;
	int incSize, incSpeed, incFood;
	int maxSize, maxSpeed, maxFood;
	int x, y;

public:
	Animal(int xAxis, int yAxis);
	~Animal();

	bool inHibernation;

	void startHibernation();
	void stopHibernation();
	void Move(Terrain *T);
	void kill();
	string getName();
	int getx();
	int gety();
	int getSize();
	int getSpeed();
	int checkHunger();
	bool checkLife();
	bool adult();	//check if fully grown
	bool canGo(char tile);	//check if animal can walk on this tile type
	virtual void incHunger();
	virtual void Raise();
	virtual void stats();
};


class Herbivore : public Animal {
private:
	bool canClimb;
	int neededFood;

public:
	Herbivore(int x, int y);

	
	void Raise();
	void incHunger();
	void stats();
	bool Eat(SeedlessPlant *p);		//Eat function for seedless plant
	bool Eat(SeededPlant *p);		//Eat function for seeded plant
	Herbivore* breed();

	friend Herbivore* Deer(int x, int y);
	friend Herbivore* Rabbit(int x, int y);
	friend Herbivore* Groundhog(int x, int y);
	friend Herbivore* Salmon(int x, int y);
};

Herbivore* Deer(int x, int y);		//Create new deer
Herbivore* Rabbit(int x, int y);	//new rabbit
Herbivore* Groundhog(int x, int y);	//new groundhog
Herbivore* Salmon(int x, int y);	//new salmon


class Carnivore : public Animal {
private:
	int attack, defence;
	int maxAttack, maxDefence;
	int incAttack, incDefence;

public:
	Carnivore(int x, int y);

	int getDefence();	//return defence stat of animal
	void incHunger();
	bool Eat(Carnivore *a);
	bool Eat(Herbivore *a);
	void Raise();
	void stats();
	Carnivore* breed();		//create need animal of the same type at the same x, y

	friend Carnivore* Fox(int x, int y);
	friend Carnivore* Wolf(int x, int y);
	friend Carnivore* Bear(int x, int y);
};

Carnivore* Fox(int x, int y);	//new fox
Carnivore* Wolf(int x, int y);	//new wolf
Carnivore* Bear(int x, int y);	//new bear
