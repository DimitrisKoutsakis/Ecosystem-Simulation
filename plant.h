#pragma once
#include <string>

class Plant {
protected:
	bool seeded;
	std::string name;
	char token;
	int breedingProb, illnessProb, life, lifeFactor;
	int x, y;

public:
	Plant(int xAxis, int yAxis);
	~Plant();
	char getToken();
	bool breed();
	virtual bool grow();
	virtual bool checkLife();
	virtual void loseLife();
};


class SeedlessPlant : public Plant {
public:
	SeedlessPlant(int x, int y);


	friend SeedlessPlant* Grass(int x, int y);
	friend SeedlessPlant* Algae(int x, int y);
};

SeedlessPlant* Grass(int x, int y);	//creates new Grass
SeedlessPlant* Algae(int x, int y);	//new Algae


class SeededPlant : public Plant {
private:
	int seeds, folliage, size;

public:
	SeededPlant(int x, int y);
	void loseLife();
	int getSize();
	bool grow();
	bool checkLife();

	friend SeededPlant* Oak(int x, int y);
	friend SeededPlant* Pine(int x, int y);
	friend SeededPlant* Maple(int x, int y);
};

SeededPlant* Oak(int x, int y);
SeededPlant* Pine(int x, int y);
SeededPlant* Maple(int x, int y);