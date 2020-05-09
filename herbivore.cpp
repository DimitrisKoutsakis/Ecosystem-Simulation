#include "animal.h"
#include <iostream>
#include "utility.h"

using namespace std;

Herbivore::Herbivore(int x, int y) : Animal(x, y) {
	token = 'H';
}

void Herbivore::incHunger() {
	Animal::incHunger();

	if (hungerCount >= 7)
		isHungry = true;
	else
		isHungry = false;
}

void Herbivore::Raise() {
	Animal::Raise();

	neededFood += incFood;
	neededFood = neededFood > maxFood ? maxFood : neededFood;

	if (size == maxSize && speed == maxSpeed && neededFood == maxFood)
		isAdult = true;
}

bool Herbivore::Eat(SeedlessPlant *p) {
	if (p->getToken() == 'A' && name != "Salmon")
		return false;
	else if (p->getToken() == 'G' && name == "Salmon")
		return false;
	
	p->loseLife();
	eatenFood += eatCount;
	if (eatenFood >= neededFood) {
		isHungry = false;
		hungerCount = 0;
		eatenFood = 0;
	}

	return true;
}

bool Herbivore::Eat(SeededPlant *p) {
	int maxPlantHeight = 0;

	if (name == "Deer")
		maxPlantHeight = size + 4;
	else if (name == "Rabbit")
		maxPlantHeight = size;
	else if (name == "Groundhog")
		maxPlantHeight = size * 3;
	else
		return false;

	if (maxPlantHeight <= p->getSize()) {
		p->loseLife();
		eatenFood += eatCount;
		if (eatenFood >= neededFood) {
			isHungry = false;
			hungerCount = 0;
			eatenFood = 0;
		}

		return true;
	}

	return false;
}

Herbivore* Herbivore::breed() {
	if (name == "Deer")
		return Deer(x, y);
	else if (name == "Rabbbit")
		return Rabbit(x, y);
	else if (name == "Groundhog")
		return Groundhog(x, y);
	else
		return Salmon(x, y);
}

void Herbivore::stats() {
	Animal::stats();

	cout << "Climb: ";
	if (canClimb)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
}

Herbivore* Deer(int x, int y) {
	Herbivore *a = new Herbivore(x, y);

	a->whitelistTiles.push_back('#');
	a->whitelistTiles.push_back('^');
	a->whitelistTiles.push_back('"');

	a->name = "Deer";
	a->hibernates = false;
	a->size = 2;
	a->speed = 4;
	a->eatCount = 2;
	a->neededFood = 8;
	a->canClimb = false;

	a->incSize = 1;
	a->incSpeed = 2;
	a->incFood = 2;

	a->maxSize = 4;
	a->maxSpeed = 8;
	a->maxFood = 8;

	return a;
}

Herbivore* Rabbit(int x, int y) {
	Herbivore *a = new Herbivore(x, y);

	a->whitelistTiles.push_back('#');
	a->whitelistTiles.push_back('"');

	a->name = "Rabbit";
	a->hibernates = false;
	a->size = 1;
	a->speed = 2;
	a->eatCount = 1;
	a->neededFood = 2;
	a->canClimb = false;

	a->incSize = 1;
	a->incSpeed = 2;
	a->incFood = 1;

	a->maxSize = 2;
	a->maxSpeed = 6;
	a->maxFood = 4;

	return a;
}

Herbivore* Groundhog(int x, int y) {
	Herbivore *a = new Herbivore(x, y);

	a->whitelistTiles.push_back('^');
	a->whitelistTiles.push_back('"');

	a->name = "Groundhog";
	a->hibernates = true;
	a->size = 2;
	a->speed = 3;
	a->eatCount = 1;
	a->neededFood = 3;
	a->canClimb = true;

	a->incSize = 1;
	a->incSpeed = 1;
	a->incFood = 1;

	a->maxSize = 3;
	a->maxSpeed = 5;
	a->maxFood = 5;

	return a;
}

Herbivore* Salmon(int x, int y) {
	Herbivore *a = new Herbivore(x, y);

	a->whitelistTiles.push_back('#');

	a->name = "Salmon";
	a->hibernates = false;
	a->size = 1;
	a->speed = 5;
	a->eatCount = 1;
	a->neededFood = 1;
	a->canClimb = false;

	a->incSize = 0;
	a->incSpeed = 0;
	a->incFood = 0;

	a->maxSize = a->size;
	a->maxSpeed = a->speed;
	a->maxFood = a->neededFood;

	return a;
}