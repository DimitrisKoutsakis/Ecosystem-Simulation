#include "plant.h"
#include "utility.h"
#include <iostream>


Plant::Plant(int xAxis, int yAxis) {
	x = xAxis;
	y = yAxis;
}

Plant::~Plant() {
}

void Plant::loseLife() {
	life -= lifeFactor > life ? life : lifeFactor;		
}

char Plant::getToken() {
	return token;
}

bool Plant::grow() {
	if (randomNum(1, 100) > illnessProb) {
		life += lifeFactor;

		return true;
	}

	loseLife();

	return false;
}

bool Plant::breed() {
	if (randomNum(1, 100) < breedingProb)
		return true;

	return false;
}

bool Plant::checkLife() {
	return life > 0;
}
