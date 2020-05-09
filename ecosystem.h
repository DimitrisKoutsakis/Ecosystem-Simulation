#pragma once
#include "animal.h"
#include "terrain.h"
#include <vector>

class Ecosystem {
private:
	int dayOfYear;
	int growthPeriodPlants, growthPeriodAnimals;
	int breedingPeriodPlants, breedingPeriodCarn, breedingPeriodHerb;

	vector<Carnivore> carnivores;
	vector<Herbivore> herbivores;
	Terrain *T;

public:
	Ecosystem(int terrrainSize);
	~Ecosystem();

	void ApplySeason();				//Every 90 days change season stats
	void PlacePlants();				// random placement of plants on terrain
	void PlaceAnimals();			// random placement of animals on the ecosystem
	int countAnimals(string name, char token);			//count amount of certain animals
	void DailyReset();				// grow plants, raise animals, Remove dead entities
	void AnimalEating();			// All animals eat if possible and if hungry
	void AnimalMovement();			// All animals move randomly on terrain
	void CheckDeadEntities();		//removes dead entities
	void AnimalBreeding();			// Breeding adult animals in breeding periods
	void PlantBreeding();			//breeding plants in breeding periods
	void MapGenerator();			//Random map generation
	int nextDay();					//Change day of the year (<=360)
	void RunEcosystem(int days);	//Start simulation
	void PrintSystem();
	void PrintPlantStatistics();
	void PrintAnimalStatistics();
	void printStats();				// Prints seasonal statistics
};

