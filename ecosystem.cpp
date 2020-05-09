#include "ecosystem.h"
#include "utility.h"
#include <iostream>


Ecosystem::Ecosystem(int terrrainSize) {
	dayOfYear = 0;
	ApplySeason();
	T = new Terrain(terrrainSize);
}

Ecosystem::~Ecosystem() {
	delete T;
}

int Ecosystem::nextDay() { return dayOfYear = dayOfYear < 360 ? dayOfYear + 1 : 1; }

void Ecosystem::AnimalMovement() {
	for (int a = 0; a < herbivores.end() - herbivores.begin(); ++a)	//move hgerbivores
		herbivores[a].Move(T);

	for (int a = 0; a < carnivores.end() - carnivores.begin(); ++a)	//move carnivores
		carnivores[a].Move(T);
}

void Ecosystem::AnimalEating() {
	for (int a = 0; a < herbivores.end() - herbivores.begin(); ++a)	//herbivores
		if (herbivores[a].checkHunger() >= 7) {			//eat 7 days after last meal
			Tile* t = &T->map[herbivores[a].getx()][herbivores[a].gety()];

			if (t->seedless)
				herbivores[a].Eat(t->seedless);
			else if (t->seeded)
				herbivores[a].Eat(t->seeded);
		}

	for (int i = 0; i < carnivores.end() - carnivores.begin(); i++) {	//carnivores
		if (carnivores[i].checkHunger())	//eat daily
			for (int j = 0; j < herbivores.end() - herbivores.begin(); j++) {
				if (!herbivores[j].checkLife())
					continue;
				else if (herbivores[j].getx() == carnivores[i].getx() && herbivores[j].gety() == carnivores[i].gety()) 
					if (carnivores[i].Eat(&herbivores[j]))
						break;
				
			}
		
		if (carnivores[i].checkHunger() >= 8)	// if crnivore hasnt eaten for 8 days eat other carnivores
			for (int j = 0; j < carnivores.end() - carnivores.begin(); j++)
				if (i == j || !carnivores[j].checkLife())
					continue;
				else if (carnivores[j].getx() == carnivores[i].getx() && carnivores[j].gety() == carnivores[i].gety())
					if (carnivores[i].Eat(&carnivores[j]))
						break;
	}
}

void Ecosystem::CheckDeadEntities() {
	for (int a = herbivores.end() - herbivores.begin() - 1; a >= 0; a--)	//delete dead herbivores
		if (!herbivores[a].checkLife())
			herbivores.erase(herbivores.begin() + a);
			

	for (int a = carnivores.end() - carnivores.begin() - 1; a >= 0; a--)	//delete dead carnivores
		if (!carnivores[a].checkLife())
			carnivores.erase(carnivores.begin() + a);

	for (int x = 0; x < T->getSize(); x++)		//delete dead platns
		for (int y = 0; y < T->getSize(); y++)
			T->map[x][y].EraseDeadPlant();
}

void Ecosystem::PlantBreeding() {
	int flag = 0;

	if (dayOfYear % breedingPeriodPlants)		//if its not breeding period return
		return;

	for (int x = 1; x < T->getSize() - 1; x++)	//search map for plant
		for (int y = 1; y < T->getSize() - 1; y++) {
			if (!T->map[x][y].getPlant())
				continue;
			else if (T->map[x][y].seeded && !T->map[x][y].seeded->breed())	//if its not time for plant to breed
				continue;
			else if (T->map[x][y].seedless && !T->map[x][y].seedless->breed())
				continue;

			for (int i = -1; i <= 1; i++) {		//find free tiles around plat
				for (int j = -1; j <= 1; j++)
					if (T->map[x+i][y+j].canPlant(T->map[x][y].getPlant())) {
						T->map[x + i][y + j].addPlant(T->map[x][y].getPlant(), x + i, y + j);	//place new plant
						flag = 1;
						break;
					}

				if (flag) {
					flag = 0;
					break;
				}
			}
		}
}

void Ecosystem::AnimalBreeding() {
	if (dayOfYear % breedingPeriodCarn == 0)	//if its breeding period for carnivores
		for (int a = carnivores.end() - carnivores.begin() - 1; a >= 0; a--)
			if (T->map[carnivores[a].getx()][carnivores[a].gety()].canSpawn(carnivores[a].getName()) && herbivores[a].adult())	//breed adult carnivores where young can spawn
				carnivores.push_back(*Bear(1,1));


	if (dayOfYear % breedingPeriodHerb == 0)	//if its breeding period for herbivores
		for (int a = herbivores.end() - herbivores.begin() - 1; a >= 0; a--)
			if (T->map[herbivores[a].getx()][herbivores[a].gety()].canSpawn(herbivores[a].getName()) && herbivores[a].adult())		//breed adult herbivores where young can spawn
				herbivores.push_back(*herbivores[a].breed());
		
}

void Ecosystem::DailyReset() {		//ecosystem daily actions
	CheckDeadEntities();		//remove dead entities

	for (int a = herbivores.end() - herbivores.begin() - 1; a >= 0; a--) {
		if (!herbivores[a].inHibernation) {	//if not in hibernation
			herbivores[a].incHunger();		//increase hunger for the day
			if (dayOfYear % growthPeriodAnimals == 0)	
				herbivores[a].Raise();		//raise stats if growth period
		}
	}
		

	for (int a = carnivores.end() - carnivores.begin() - 1; a >= 0; a--) {		//similar to herbivores
		if (!carnivores[a].inHibernation) {
			carnivores[a].incHunger();
			if (dayOfYear % growthPeriodAnimals == 0)
				carnivores[a].Raise();
		}
	}

	if (dayOfYear > 180 && dayOfYear <= 270);		//dont grow on autumn
	else if (dayOfYear % growthPeriodPlants == 0)
		for (int x = 0; x < T->getSize(); x++)
			for (int y = 0; y < T->getSize(); y++)
				if (T->map[x][y].getPlant())
					if (T->map[x][y].seeded)
						T->map[x][y].seeded->grow();
					else
						T->map[x][y].seedless->grow();

	CheckDeadEntities();
}

void Ecosystem::MapGenerator() {		//generate terrain
	T->GenerateRiver();
	T->GenerateLake();
	T->GenerateHills(randomNum(3, 5));
	T->GenerateMeadow();
}

void Ecosystem::ApplySeason() {		//set seasonal stats
	if (dayOfYear == 0) {			//Spring
		growthPeriodPlants = 5;
		growthPeriodAnimals = 20;
		breedingPeriodPlants = 10;
		breedingPeriodHerb = 12;
		breedingPeriodCarn = 11;

		for (int a = herbivores.end() - herbivores.begin() - 1; a >= 0; a--)		//stop hibernation
			herbivores[a].stopHibernation();

		for (int a = carnivores.end() - carnivores.begin() - 1; a >= 0; a--)
			carnivores[a].stopHibernation();
	}
	else if (dayOfYear == 90) {		//Summer
		growthPeriodPlants = 10;
		growthPeriodAnimals = 30;
		breedingPeriodPlants = 10;
		breedingPeriodHerb = 8;
		breedingPeriodCarn = 9;
	}
	else if (dayOfYear == 180) {	//Autumn
		growthPeriodPlants = 999;
		growthPeriodAnimals = 15;
		breedingPeriodPlants = 20;
		breedingPeriodHerb = 5;
		breedingPeriodCarn = 9;
	}
	else if (dayOfYear == 270) {	//Winter
		growthPeriodPlants = 10;
		growthPeriodAnimals = 30;
		breedingPeriodPlants = 10;
		breedingPeriodHerb = 18;
		breedingPeriodCarn = 10;

		for (int a = herbivores.end() - herbivores.begin() - 1; a >= 0; a--)		//start hibernation
			herbivores[a].startHibernation();

		for (int a = carnivores.end() - carnivores.begin() - 1; a >= 0; a--)
			carnivores[a].startHibernation();
	}
}

int Ecosystem::countAnimals(string name, char token) {
	int counter = 0;

	if (token == 'C') {
		for (int a = carnivores.end() - carnivores.begin() - 1; a >= 0; a--)
			if (carnivores[a].getName() == name)
				counter++;
	} 
	else if (token == 'H') {
		for (int a = herbivores.end() - herbivores.begin() - 1; a >= 0; a--)
			if (herbivores[a].getName() == name)
				counter++;
	}

	return counter;
}

void Ecosystem::PrintSystem() {
	T->printMap();
	
	std::cout << "Day of Year: " << dayOfYear
		<< endl << "Animals: " << carnivores.size() + herbivores.size()
		<< endl << "Carnivores: " << carnivores.size()
		<< endl << "Herbivores: " << herbivores.size() << endl;

	std::cout << endl << "Plants: " << T->countPlants() << endl;
}

void Ecosystem::PrintAnimalStatistics() {
	std::cout << "Deers: " << countAnimals("Deer", 'H')
		<< endl << "Rabbits: " << countAnimals("Rabbit", 'H')
		<< endl << "Groundhogs: " << countAnimals("Groundhog", 'H')
		<< endl << "Salmons: " << countAnimals("Salmon", 'H')
		<< endl << "Foxes: " << countAnimals("Fox", 'C')
		<< endl << "Wolves: " << countAnimals("Wolf", 'C')
		<< endl << "Bears: " << countAnimals("Bear", 'C') << endl;
}

void Ecosystem::PrintPlantStatistics() {
	std::cout << "Grass: " << T->countPlants('G')
		<< endl << "Algae: " << T->countPlants('A')
		<< endl << "Oaks: " << T->countPlants('O')
		<< endl << "Pines: " << T->countPlants('P')
		<< endl << "Maples: " << T->countPlants('M') << endl;
}

void Ecosystem::printStats() {
	cout << endl;
	PrintSystem();
	cout << endl;
	PrintAnimalStatistics();
	cout << endl;
	PrintPlantStatistics();
	cout << endl;
}

void Ecosystem::RunEcosystem(int days) {
	for (int d = 0; d < days; d++) {
		if (d % 90 == 0) {
			ApplySeason();
			printStats();
		}

		AnimalBreeding();					//in breeding periods
		PlantBreeding();

		for (int h = 0; h < 24; h++) {		//animals move and search for good every hour
			AnimalMovement();
			AnimalEating();
		}

		DailyReset();
		nextDay();
	}

	if (days % 90)
		printStats();
}

void Ecosystem::PlacePlants() {
	int max = randomNum(T->getSize(), 2 * T->getSize());
	int x, y;

	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canPlant('G'))
			T->map[x][y].addPlant('G', x, y);
		else
			i--;

	}

	max = randomNum(T->getSize(), 2 * T->getSize());
	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canPlant('A'))
			T->map[x][y].addPlant('A', x, y);
		else
			i--;
	}

	max = randomNum(T->getSize(), 2 * T->getSize());
	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canPlant('O'))
			T->map[x][y].addPlant('O', x, y);
		else
			i--;
	}

	max = randomNum(T->getSize() / 3, T->getSize() / 2);
	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canPlant('P'))
			T->map[x][y].addPlant('P', x, y);
		else
			i--;
	}

	max = randomNum(T->getSize(), 2 * T->getSize());
	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canPlant('M'))
			T->map[x][y].addPlant('M', x, y);
		else
			i--;
	}
}

void Ecosystem::PlaceAnimals() {
	int max = randomNum(T->getSize(), 2 * T->getSize());
	int x, y;

	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canSpawn("Deer"))
			herbivores.push_back(*Deer(x, y));
		else
			i--;
	}

	max = randomNum(T->getSize(), 2 * T->getSize());
	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canSpawn("Rabbit"))
			herbivores.push_back(*Rabbit(x, y));
		else
			i--;
	}

	max = randomNum(T->getSize(), 2 * T->getSize());
	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canSpawn("Groundhog"))
			herbivores.push_back(*Groundhog(x, y));
		else
			i--;
	}

	randomNum(T->getSize() / 3, T->getSize() / 2);
	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canSpawn("Salmon"))
			herbivores.push_back(*Salmon(x, y));
		else
			i--;
	}

	max = randomNum(T->getSize() / 3, T->getSize() / 2);
	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canSpawn("Fox"))
			carnivores.push_back(*Fox(x, y));
		else
			i--;
	}

	max = randomNum(T->getSize() / 3, T->getSize() / 2);
	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canSpawn("Wolf"))
			carnivores.push_back(*Wolf(x, y));
		else
			i--;
	}

	max = randomNum(T->getSize() / 3, T->getSize() / 2);
	for (int i = 0; i < max; i++) {
		x = randomNum(0, T->getSize() - 1);
		y = randomNum(0, T->getSize() - 1);

		if (T->map[x][y].canSpawn("Bear"))
			carnivores.push_back(*Bear(x, y));
		else
			i--;
	}
}

