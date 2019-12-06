#include <iostream>
#include <fstream>
#include <vector>

#include "Day1.hpp"

void day1() {
	std::ifstream inputFile("Data/Day1.txt");
	int tempModuleMass;
	std::vector<int> moduleMasses;
	std::vector<int> moduleFuelConsumptions;

	while (inputFile >> tempModuleMass) {
		int initialTempModuleMass = tempModuleMass;
		moduleMasses.push_back(initialTempModuleMass);

		// Part 1
		//int fuelConsumption = (tempModuleMass / 3) - 2; 

		// Part 2
		int tempTotalFuelConsumption = 0;
		//int fuelConsumption = (tempModuleMass / 3) - 2;
		//tempTotalFuelConsumption += fuelConsumption;
		while ((tempModuleMass / 3) - 2 > 0) {
			int fuelConsumption = ((tempModuleMass / 3) - 2);
			tempTotalFuelConsumption += fuelConsumption;
			tempModuleMass = fuelConsumption;
		}


		moduleFuelConsumptions.push_back(tempTotalFuelConsumption);

		std::cout << initialTempModuleMass << " " << tempTotalFuelConsumption << std::endl;
	}

	int totalFuelConsumption = 0;
	for (auto i = moduleFuelConsumptions.begin(); i != moduleFuelConsumptions.end(); ++i) {
		totalFuelConsumption += *i;
	}

	std::cout << std::endl << totalFuelConsumption;
}