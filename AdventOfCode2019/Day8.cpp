#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <tuple>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "Day8.hpp"

void day8() {
	std::ifstream inputFile("Day8.txt");
	std::string line;
	std::getline(inputFile, line);

	std::vector<int> numbers;
	
	const int WIDTH = 25;
	const int HEIGHT = 6;
	const int LAYERS_COUNT = 100;

	int x = 0;
	int y = 0;
	int layer = 0;

	std::vector<std::vector<std::vector<int>>> layers(LAYERS_COUNT);
	layers[0] = std::vector<std::vector<int>>(HEIGHT);
	layers[0][0] = std::vector<int>(WIDTH);

	for (int i = 0; i < line.size(); ++i) {
		int currentNumber = std::stoi(line.substr(i, 1));
		layers[layer][y][x] = currentNumber;
		x++;
		if (i == 14999) {
			break;
		}
		if (x % WIDTH == 0) {
			x = 0;
			y++;
			if (y % HEIGHT == 0) {
				y = 0;
				layer++;
				layers[layer] = std::vector<std::vector<int>>(HEIGHT);
			}
			layers[layer][y] = std::vector<int>(WIDTH);
		}
	}

	std::map<int, int> count0;
	std::map<int, int> count1;
	std::map<int, int> count2;

	int layerWithFewer0 = -1;
	int minNumber0 = WIDTH * HEIGHT;

	int i = 0;
	int lol = 0;
	for (auto itLayer = layers.begin(); itLayer != layers.end(); ++itLayer) {
		count0[i] = 0;
		count1[i] = 0;
		count2[i] = 0;

		for (auto itHeight = itLayer->begin(); itHeight != itLayer->end(); ++itHeight) {
			for (auto itWidth = itHeight->begin(); itWidth != itHeight->end(); ++itWidth) {
				lol++;
				switch (*itWidth)
				{
				case 0:
					count0[i]++;
					break;
				case 1:
					count1[i]++;
					break;
				case 2:
					count2[i]++;
					break;
				}
			}
		}

		if (count0[i] < minNumber0) {
			minNumber0 = count0[i];
			layerWithFewer0 = i;
		}

		//std::cout << "Layer " << i << " 0: " << count0[i] << " 1: " << count1[i] << " 2: " << count2[i] << std::endl;

		i++;
	}

	//std::cout << "Layer with Min 0: " << layerWithFewer0 << "(" << minNumber0 << ") - Mult: " << (count1[layerWithFewer0] * count2[layerWithFewer0]) << std::endl;

	//for (auto i = numbers.begin(); i != numbers.end(); ++i)
	//	std::cout << *i << ' ';
	
	std::vector<std::vector<int>> finalMessage = std::vector<std::vector<int>>(HEIGHT);
	for (int y = 0; y < HEIGHT; ++y) {
		finalMessage[y] = std::vector<int>(WIDTH);
	}

	std::cout << std::endl << std::endl;
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			int layer = 0;
			while (layers[layer][y][x] == 2) {
				layer++;
			}
			int value = layers[layer][y][x];
			finalMessage[y][x] = value;
			std::cout << (value == 1 ? "x" : " ");
		}
		std::cout << std::endl;
	}
}