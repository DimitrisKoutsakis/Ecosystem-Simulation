#include "plant.h"
#include "utility.h"

SeedlessPlant::SeedlessPlant(int x, int y): Plant(x, y) {
	seeded = false;
}

SeedlessPlant* Grass(int x, int y) {
	SeedlessPlant *p = new SeedlessPlant(x, y);

	p->name = "Grass";
	p->token = 'G';
	p->breedingProb = 15;
	p->illnessProb = 15;
	p->life = 5;
	p->lifeFactor = 4;

	return p;
}

SeedlessPlant* Algae(int x, int y) {
	SeedlessPlant *p = new SeedlessPlant(x, y);

	p->name = "Algae";
	p->token = 'A';
	p->breedingProb = 25;
	p->illnessProb = 25;
	p->life = 5;
	p->lifeFactor = 2;

	return p;
}
