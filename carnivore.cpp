#include "animal.h"
#include <iostream>
#include "utility.h"

using namespace std;

Carnivore::Carnivore(int x, int y) : Animal(x, y) {
	token = 'C';
}

void Carnivore::incHunger() {
	Animal::incHunger();

	if (hungerCount)
		isHungry = true;
}

int Carnivore::getDefence() {
	return defence;
}

bool Carnivore::Eat(Carnivore *a) {
	if (hungerCount < 8 || name == a->getName())
		return false;

	if (name == "Bear" || size > a->getSize() || attack > a->getDefence()) {
		a->kill();
		isHungry = false;
		hungerCount = 0;
		eatenFood += eatCount;
		return true;
	} 

	return false;
}

bool Carnivore::Eat(Herbivore *a) {
	if ((size > a->getSize() && speed > a->getSpeed()) || name == "Bear") {
		a->kill();
		isHungry = false;
		hungerCount = 0;
		eatenFood += eatCount;
		return true;
	}

	return false;
}

void Carnivore::Raise() {
	Animal::Raise();

	eatCount += incFood;
	eatCount = eatCount > maxFood ? maxFood : eatCount;

	attack += incAttack;
	attack = attack > maxAttack ? maxAttack : attack;

	defence += incDefence;
	defence = defence > maxDefence ? maxDefence : defence;

	if (size == maxSize && speed == maxSpeed && attack == maxAttack && defence == maxDefence)
		isAdult = true;
}

Carnivore* Carnivore::breed() {
	if (name == "Fox")
		return Fox(x, y);
	else if (name == "Wolf")
		return Wolf(x, y);
	else
		return Bear(x, y);
}

void Carnivore::stats() {
	Animal::stats();
	cout << "ATK: " << attack << endl;
	cout << "DEF: " << defence << endl;
}

Carnivore* Fox(int x, int y) {
	Carnivore *a = new Carnivore(x, y);

	a->whitelistTiles.push_back('#');
	a->whitelistTiles.push_back('"');
	a->whitelistTiles.push_back('^');

	a->name = "Fox";
	a->hibernates = false;
	a->size = 1;
	a->speed = 1;
	a->eatCount = 2;
	a->attack = 1;
	a->defence = 1;

	a->incSize = 1;
	a->incSpeed = 1;
	a->incFood = 1;
	a->incAttack = 1;
	a->incDefence = 1;

	a->maxSize = 4;
	a->maxAttack = 5;
	a->maxDefence = 5;
	a->maxSpeed = 6;
	a->maxFood = 6;

	return a;
}

Carnivore* Wolf(int x, int y) {
	Carnivore *a = new Carnivore(x, y);

	a->whitelistTiles.push_back('#');
	a->whitelistTiles.push_back('^');
	a->whitelistTiles.push_back('"');

	a->name = "Wolf";
	a->hibernates = false;
	a->size = 1;
	a->speed = 2;
	a->eatCount = 2;
	a->attack = 2;
	a->defence = 2;

	a->incSize = 1;
	a->incSpeed = 2;
	a->incFood = 2;
	a->incAttack = 2;
	a->incDefence = 2;

	a->maxSize = 7;
	a->maxAttack = 8;
	a->maxDefence = 6;
	a->maxSpeed = 8;
	a->maxFood = 8;

	return a;
}

Carnivore* Bear(int x, int y) {
	Carnivore *a = new Carnivore(x, y);

	a->whitelistTiles.push_back('#');
	a->whitelistTiles.push_back('^');
	a->whitelistTiles.push_back('"');

	a->name = "Bear";
	a->hibernates = true;
	a->size = 3;
	a->speed = 4;
	a->eatCount = 5;
	a->attack = 6;
	a->defence = 6;

	a->incSize = 2;
	a->incSpeed = 0;
	a->incFood = 2;
	a->incAttack = 2;
	a->incDefence = 2;

	a->maxSize = 10;
	a->maxAttack = 10;
	a->maxDefence = 10;
	a->maxSpeed = 4;
	a->maxFood = 10;

	return a;
}