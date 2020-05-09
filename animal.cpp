#include "animal.h"
#include "utility.h"
#include <iostream>

using namespace std;

Animal::Animal(int xAxis, int yAxis) {
	x = xAxis;
	y = yAxis;
	eatenFood = 0;
	hungerCount = 0;
	isAlive = true;
	isAdult = false;
	isHungry = false;
	inHeat = false;
	inHibernation = false;
}


Animal::~Animal() {}

int Animal::getx() { return x; }

int Animal::gety() { return y; }

int Animal::getSize() { return size; }

int Animal::getSpeed() { return speed; }

string Animal::getName() { return name; }

void Animal::kill() { isAlive = false; }	// Kill animal

int Animal::checkHunger() { return hungerCount; }	// Return days without food

bool Animal::checkLife() { return isAlive; }	// Check is animal is alive

bool Animal::adult() { return isAdult; }		// check if animal is fully grown

void Animal::incHunger() {		// increase hunger
	if (++hungerCount == 10)	// if 10 days without food kill animal
		kill();
}

void Animal::startHibernation() {
	if (hibernates)
		inHibernation = true;
}

void Animal::stopHibernation() {
	if (hibernates)
		inHibernation = false;
}

bool Animal::canGo(char tile) {		//check if animal can walk on this tile type
	for (int t = 0; t < whitelistTiles.end() - whitelistTiles.begin(); t++)
		if (whitelistTiles[t] == tile)
			return true;
			

	return false;
}

void Animal::Move(Terrain *T) {		// Move on terrain
	int opX, opY, buffer = 5;

	while (buffer--) {				// Try maximum 5 times to move
		opX = randomNum(-speed / 2, speed / 2);		// Randomize distance and direction dependent on speed
		opY = randomNum(-speed / 2, speed / 2);

		if (x + opX >= T->getSize())
			opX = T->getSize() - x - 1;
		else if (x + opX < 0)
			opX = -x;

		if (y + opY >= T->getSize())
			opY = T->getSize() - y - 1;
		else if (y + opX < 0)
			opY = -y;

		if (canGo(T->map[x + opX][y + opY].getType())) {
			x += opX;
			y += opY;
			return;
		}

	}
}

void Animal::Raise() {		// Increase animal stats (on growth period)
	size += incSize;
	size = size > maxSize ? maxSize : size;

	speed += incSpeed;
	speed = speed > maxSpeed ? maxSpeed : speed;
}

void Animal::stats() {		//prints animals stats
	cout << name << " (" << token << ")" << endl;
	cout << "Status: ";
	
	if (isAlive) {
		cout << "Alive";
		if (isHungry)
			cout << ", Hungry";
		if (inHibernation)
			cout << ", Hibernates";
		else if(inHeat)
			cout << ", in Heat";
	}
	else
		cout << "Dead";
	
	if (isAdult)
		cout << ", Adult" << endl;
	else
		cout << endl;

	cout << "Size: " << size << endl;
	cout << "Speed: " << speed << endl;
}
