#pragma once
#include <string>
#include <vector>
#include "plant.h"

using namespace std;

class Tile {
private:
	char type, plantToken;
	vector<string> whitelistSpawn;
	vector<char> whitelistPlants;

public:
	SeededPlant *seeded;
	SeedlessPlant *seedless;

	Tile();
	~Tile();

	char getType();		//return tile type
	char getPlant();	//return plant type on tile
	void addWater();	//make tile water type
	void addHill();		//make tile hill type
	void addMeadow();	//make tile meadow type
	bool canSpawn(string a);	//check if animal with name a can spawn on tile
	bool canPlant(char p);		//check if plant with token p can be planted on tile
	void addPlant(char p, int x, int y);
	void EraseDeadPlant();
};

