#include "utility.h"
#include <cstdlib>
#include <iostream>

int randomNum(int min, int max) {		//generates random nuber between min and max (max included)
	return min == max ? min : ((rand() % (max-min+1)) + min);
}