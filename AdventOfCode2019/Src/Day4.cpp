#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <cstdlib>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "Day4.hpp"

bool isValidPassword(int number);

void day4() {
	std::ifstream inputFile("Data/Day4.txt");
	std::string line;
	std::getline(inputFile, line);

	std::vector<std::string> numbersStr;
	boost::split(numbersStr, line, boost::is_any_of("-"), boost::token_compress_on);

	std::vector<int> numbers;
	std::transform(numbersStr.begin(), numbersStr.end(), std::back_inserter(numbers), &boost::lexical_cast<int, std::string>);

	// Cheating
	int minNumber = numbers[0];
	int maxNumber = numbers[1];
	
	int countValidPassword = 0;
	for (int i = minNumber; i < maxNumber; ++i) {
		if (isValidPassword(i)) {
			countValidPassword++;
		}
	}
	
	std::cout << countValidPassword << std::endl;
}

bool isValidPassword(int number) {
	std::string numberStr = std::to_string(number);

	//It is a six - digit number.
	//The value is within the range given in your puzzle input.
	// Handled by for loop

	//Two adjacent digits are the same(like 22 in 122345).
	if (!(
		(										numberStr.at(0) == numberStr.at(1) && numberStr.at(1) != numberStr.at(2)) ||
		(numberStr.at(0) != numberStr.at(1) &&	numberStr.at(1) == numberStr.at(2) && numberStr.at(2) != numberStr.at(3)) ||
		(numberStr.at(1) != numberStr.at(2) &&	numberStr.at(2) == numberStr.at(3) && numberStr.at(3) != numberStr.at(4)) ||
		(numberStr.at(2) != numberStr.at(3) &&	numberStr.at(3) == numberStr.at(4) && numberStr.at(4) != numberStr.at(5)) ||
		(numberStr.at(3) != numberStr.at(4) &&	numberStr.at(4) == numberStr.at(5)										)
			)) {
			return false;
	}

	//Going from left to right, the digits never decrease; they only ever increase or stay the same(like 111123 or 135679).
	if (numberStr.at(0) > numberStr.at(1) || 
		numberStr.at(1) > numberStr.at(2) || 
		numberStr.at(2) > numberStr.at(3) || 
		numberStr.at(3) > numberStr.at(4) || 
		numberStr.at(4) > numberStr.at(5)) {
		return false;
	}

	return true;
}