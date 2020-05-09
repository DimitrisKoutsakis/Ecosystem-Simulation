eco : main.cpp tile.cpp terrain.cpp animal.cpp carnivore.cpp herbivore.cpp plant.cpp seedlessPlant.cpp seededPlant.cpp utility.cpp ecosystem.cpp
	g++ -o eco main.cpp tile.cpp terrain.cpp animal.cpp carnivore.cpp herbivore.cpp plant.cpp seedlessPlant.cpp seededPlant.cpp utility.cpp ecosystem.cpp

clean: eco
	rm eco