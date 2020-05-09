#include "tile.h"
#include <algorithm>
#include <iostream>

Tile::Tile() {
	type = '-';
	seeded = NULL;
	seedless = NULL;
	plantToken = 0;
}

Tile::~Tile() {
	if (seeded)
		delete seeded;
	else if (seedless)
		delete seedless;
};

char Tile::getType() { return type; }

char Tile::getPlant() { return plantToken; }		//return token of plant in tile

bool Tile::canSpawn(string a) {		//check if animal with name a can spawn on tile
	for (int i = 0; i < whitelistSpawn.end() - whitelistSpawn.begin(); ++i)
		if (whitelistSpawn[i] == a)
			return true;

	return false;
}

bool Tile::canPlant(char p) {		//check if plant with token p can be planted on tile
	if (plantToken)
		return false;


	for (int i = 0; i < whitelistPlants.end() - whitelistPlants.begin(); ++i)
		if (whitelistPlants[i] == p)
			return true;

	return false;
}
	
void Tile::addPlant(char p, int x, int y) {		// add plant on tile
	if (plantToken)		//check if tile has already plant
		return;
	else
		plantToken = p;

	if (p == 'G')
		seedless = Grass(x, y);
	else if (p == 'A')
		seedless = Algae(x, y);
	else if (p == 'O')
		seeded = Oak(x, y);
	else if (p = 'P')
		seeded = Pine(x, y);
	else
		seeded = Maple(x, y);
	
}

void Tile::EraseDeadPlant() {		//delete dead plant from tile
	if (seeded && !seeded->checkLife()) {
		delete seeded;
		seeded = NULL;
		plantToken = 0;
	}
	else if (seedless && !seedless->checkLife()) {
		delete seedless;
		seedless = NULL;
		plantToken = 0;
	}
}

void Tile::addWater() {		//make tile of type water
	type = '#';
	whitelistPlants.push_back('A');

	whitelistSpawn.push_back("Salmon");
}

void Tile::addHill() {		//make tile of type hill
	type = '^';
	whitelistPlants.push_back('M');
	whitelistPlants.push_back('P');

	whitelistSpawn.push_back("Wolf");
	whitelistSpawn.push_back("Bear");
}

void Tile::addMeadow() {		//make tile of type meadow
	type = '"';
	whitelistPlants.push_back('G');
	whitelistPlants.push_back('M');
	whitelistPlants.push_back('O');

	whitelistSpawn.push_back("Deer");
	whitelistSpawn.push_back("Rabbit");
	whitelistSpawn.push_back("Groundhog");
	whitelistSpawn.push_back("Fox");
	whitelistSpawn.push_back("Wolf");
}


