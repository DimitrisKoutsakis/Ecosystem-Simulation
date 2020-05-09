#include <iostream>
#include "terrain.h"
#include "utility.h"

using namespace std;

Terrain::Terrain(int size) {
	terrainSize = size;

	map = new Tile*[size];
	for (int i = 0; i < size; i++)
		map[i] = new Tile[size];
}

Terrain::~Terrain() {
	for (int i = 0; i < terrainSize; i++)
		delete[] map[i];

	delete map;
}

int Terrain::getSize() { return terrainSize; }

void Terrain::printMap() {		// print map with plant tokens
	for (int i = 0; i < terrainSize; i++) {
		for (int j = 0; j < terrainSize; j++)
			if(map[j][i].getPlant())
				cout << map[j][i].getPlant() << " ";
			else
				cout << map[j][i].getType() << " ";

		cout << endl;
	}
}

void Terrain::GenerateRiver() {
	int y = 0, x = randomNum(5, terrainSize - 5);
	int diverge;

	map[x][y].addWater();

	while (++y < terrainSize) {
		if (randomNum(1, 100) > 30) {	//chance to not diverge
			map[x][y].addWater();
			continue;
		}

		diverge = randomNum(0, 1) ? 1 : -1;		//diverge left or right

		if (x + diverge >= 0 && x + diverge < terrainSize)
			x += diverge;

		map[x][y].addWater();
		diverge = randomNum(0, 1) ? diverge : 0;	//chance to diverge 2 tiles

		if (x + diverge >= 0 && x + diverge < terrainSize)
			x += diverge;

		map[x][y].addWater();
	}
}

void Terrain::GenerateLake() {		//create random sized lake
	int lakeSize = randomNum(3, terrainSize / 2);
	int x = randomNum(0, terrainSize - lakeSize);
	int y = randomNum(0, terrainSize - lakeSize);

	for (int i = 0; i < lakeSize; i++)
		for (int j = 0; j < lakeSize; j++)
			map[x + i][y + j].addWater();
}

void Terrain::GenerateHills(int n) {		//create n amount of hills
	int size, x, y, i = n;

	while (i--) {
		size = randomNum(2, 4);

		x = randomNum(0, terrainSize - size);
		y = randomNum(0, terrainSize - size);

		if (map[x][y].getType() == '#' || map[x][y].getType() == '^') {		//avoid water tiles
			i++;
			continue;
		}

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if(map[x + i][y + j].getType() != '#')		//dont cjance water tiles
					map[x + i][y + j].addHill();
	}
}

void Terrain::GenerateMeadow() {				//fill empty tiles with meadow
	for (int x = 0; x < terrainSize; x++)
		for (int y = 0; y < terrainSize; y++)
			if (map[x][y].getType() != '#' && map[x][y].getType() != '^')
				map[x][y].addMeadow();
}

int Terrain::countPlants(char type) {		//count amount of plant of certain type of all plants
	int counter = 0;

	if (type == '0') {		//count all plants
		for (int i = 0; i < terrainSize; i++)
			for (int j = 0; j < terrainSize; j++)
				if (map[j][i].getPlant())
					counter++;
	}	
	else {			//count plants of type
		for (int i = 0; i < terrainSize; i++)
			for (int j = 0; j < terrainSize; j++)
				if (map[j][i].getPlant() == type)
					counter++;
	}
	
	return counter;
}
