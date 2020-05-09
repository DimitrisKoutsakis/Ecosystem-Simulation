#include <iostream>
#include "ecosystem.h"
#include "plant.h"
#include "animal.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
	srand(time(NULL));

	int size;
	cout << "Input terrain size: ";
	cin >> size;
	size = size < 10 ? 10 : size;

	Ecosystem E(size);

	E.MapGenerator();
	E.PlaceAnimals();
	E.PlacePlants();

	int days;
	cout << "input days for simulation: ";
	cin >> days;

	E.RunEcosystem(days);
}