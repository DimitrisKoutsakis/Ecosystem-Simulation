#pragma once

#include "tile.h"

class Terrain {
private:
	int terrainSize;

public:

	Tile **map;

	Terrain(int size);
	~Terrain();
	int getSize();
	void GenerateRiver();
	void GenerateLake();
	void GenerateHills(int n);
	void GenerateMeadow();
	int countPlants(char type = '0');
	void printMap();
};

