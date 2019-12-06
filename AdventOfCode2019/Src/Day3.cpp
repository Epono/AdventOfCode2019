#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <cstdlib>

#include <boost/algorithm/string.hpp>

#include "Day3.hpp"

std::unordered_map<int, std::unordered_map<int, bool>> fillMap(std::vector<std::string>& instructions);
bool mapsOverlapAtCoordinate(std::unordered_map<int, std::unordered_map<int, bool>>& map1, std::unordered_map<int, std::unordered_map<int, bool>>& map2, int x, int y);

void day3() {
	std::ifstream inputFile("Data/Day3.txt");
	std::string line1, line2;
	std::getline(inputFile, line1);
	std::getline(inputFile, line2);
	std::cout << line1 << std::endl << std::endl << line2 << std::endl << std::endl;

	std::vector<std::string> instructionsLine1;
	std::vector<std::string> instructionsLine2;
	boost::split(instructionsLine1, line1, boost::is_any_of(","), boost::token_compress_on);
	boost::split(instructionsLine2, line2, boost::is_any_of(","), boost::token_compress_on);
	
	auto map1 = fillMap(instructionsLine1);
	auto map2 = fillMap(instructionsLine2);

	std::pair<int, int> closestIntersection(0, 0);
	int closestDistance = 99999999;

	for (std::unordered_map<int, std::unordered_map<int, bool>>::iterator it = map1.begin(); it != map1.end(); ++it) {
		int x = it->first;
		for (std::unordered_map<int, bool>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			int y = it2->first;

			bool overlap = mapsOverlapAtCoordinate(map1, map2, x, y);

			if (overlap) {
				int distance = abs(x) + abs(y);
				//std::cout << distance << " ";
				if (distance < closestDistance) {
					closestIntersection.first = x;
					closestIntersection.second = y;
					closestDistance = distance;
					std::cout << "New closest : " << closestIntersection.first << "," << closestIntersection.second << " - Distance : " << closestDistance << std::endl;
				}
				
			}
		}
	}

}

std::unordered_map<int, std::unordered_map<int, bool>> fillMap(std::vector<std::string>& instructions) {
	std::unordered_map<int, std::unordered_map<int, bool>> map; 
	std::pair<int, int> currentPosition(0, 0);

	for (auto instruction = instructions.begin(); instruction != instructions.end(); ++instruction) {
		char direction = instruction->at(0);
		int number = std::stoi(instruction->substr(1));
		//std::cout << *instruction << ": " << direction << " " << number << std::endl;

		switch (direction)
		{
		case 'U':
			for (int y = 0; y < number; ++y) {
				currentPosition.second++;
				map[currentPosition.first][currentPosition.second] = true;
			}
			break;
		case 'R':
			for (int x = 0; x < number; ++x) {
				currentPosition.first++;
				map[currentPosition.first][currentPosition.second] = true;
			}
			break;
		case 'D':
			for (int y = 0; y < number; ++y) {
				currentPosition.second--;
				map[currentPosition.first][currentPosition.second] = true;
			}
			break;
		case 'L':
			for (int x = 0; x < number; ++x) {
				currentPosition.first--;
				map[currentPosition.first][currentPosition.second] = true;
			}
			break;
		}
	}

	return map;
}

bool mapsOverlapAtCoordinate(std::unordered_map<int, std::unordered_map<int, bool>>& map1, std::unordered_map<int, std::unordered_map<int, bool>>& map2, int x, int y) {
	if (map1.find(x) != map1.end() && map2.find(x) != map2.end()) {
		if (map1[x].find(y) != map1[x].end() && map2[x].find(y) != map2[x].end()) {
			return true;
		}
	}
	return false;
}