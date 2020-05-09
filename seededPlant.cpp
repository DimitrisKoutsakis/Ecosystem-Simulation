#include "plant.h"
#include "utility.h"

SeededPlant::SeededPlant(int x, int y) : Plant(x, y) {
	seeded = true;
}

void SeededPlant::loseLife() {		//loselifge on seeded plants
	int prevFolliage = folliage;

	for (int i = 0; i < lifeFactor; i++)
		if (!life)					//if dead return
			return;
		else if (seeds)				//prioritize seed
			seeds--;
		else if (folliage) {		//else remove folliage and hp
			folliage--;
			life -= life ? 1 : 0;
		}
}

int SeededPlant::getSize() { return size; }

bool SeededPlant::grow() {
	int op = randomNum(1, 100) > illnessProb ? 1 : -1;		//if illness remove stats else add

	folliage += op * lifeFactor;
	if (folliage < 0)
		folliage = 0;

	life += op * lifeFactor;
	if (life < 0)
		life = 0;

	seeds += 2 * op * lifeFactor;
	if (seeds < 0)
		seeds = 0;

	if (!(folliage % lifeFactor))
		size += op;

	return op > 0;
}

bool SeededPlant::checkLife() {			// if life orr size or folliage == 0 plant is dead
	return life > 0 && size > 0 && folliage > 0;
}


SeededPlant* Maple(int x, int y) {
	SeededPlant *p = new SeededPlant(x, y);

	p->name = "Maple";
	p->token = 'M';
	p->breedingProb = 5;
	p->illnessProb = 5;
	p->seeds = 10;
	p->folliage = 20;
	p->size = 2;
	p->life = p->folliage;
	p->lifeFactor = 10;

	return p;
}

SeededPlant* Oak(int x, int y) {
	SeededPlant *p = new SeededPlant(x, y);

	p->name = "Oak";
	p->token = 'O';
	p->breedingProb = 20;
	p->illnessProb = 20;
	p->seeds = 15;
	p->folliage = 30;
	p->size = 5;
	p->life = p->folliage;
	p->lifeFactor = 15;

	return p;
}

SeededPlant* Pine(int x, int y) {
	SeededPlant *p = new SeededPlant(x, y);

	p->name = "Pine";
	p->token = 'P';
	p->breedingProb = 15;
	p->illnessProb = 15;
	p->seeds = 20;
	p->folliage = 40;
	p->size = 5;
	p->life = p->folliage;
	p->lifeFactor = 20;

	return p;
}