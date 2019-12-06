#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "Day2.hpp"

int run_day2(std::vector<int> &values, int noun, int verb);

void day2() {
	std::ifstream inputFile("Data/Day2.txt");
	std::string line;
	std::getline(inputFile, line);

	std::vector<std::string> strings;
	boost::split(strings, line, boost::is_any_of(","), boost::token_compress_on);

	std::vector<int> numbersOriginal;

	//std::transform(strings.begin(), strings.end(), std::back_inserter(numbers), [](const std::string& str) { return std::stoi(str); });
	std::transform(strings.begin(), strings.end(), std::back_inserter(numbersOriginal), &boost::lexical_cast<int, std::string>);

	std::vector<int> numbers(numbersOriginal.size());

	// PART 1
	//std::copy(numbersOriginal.begin(), numbersOriginal.end(), numbers.begin());
	//int result = run_day2(numbers, 12, 2);

	// PART 2
	int nounPlusVerb = 0;
	for (int noun = 0; noun <= 99; ++noun) {
		for (int verb = 0; verb <= 99; ++verb) {
			std::copy(numbersOriginal.begin(), numbersOriginal.end(), numbers.begin());
			int result = run_day2(numbers, noun, verb);
			if (result == 19690720) {
				nounPlusVerb = 100 * noun + verb;
				break;
			}
		}
		if (nounPlusVerb != 0) {
			break;
		}
	}

	std::cout << "RESULT: " << nounPlusVerb << std::endl;
}

int run_day2(std::vector<int> &values, int noun, int verb) {
	// Replacing values
	values[1] = noun;
	values[2] = verb;

	//int index = 0;
	//for (auto number = values.begin(); values != values.end(); ++number) {
	//	std::cout << *number;
	//	if (index % 4 == 3) {
	//		std::cout << std::endl;
	//	}
	//	else {
	//		std::cout << " ";
	//	}
	//	index++;
	//}

	int cursorPosition = 0;
	int opcode = values[cursorPosition * 4];
	while (opcode != 99) {
		int opcode = values[cursorPosition * 4];

		if (opcode == 99)
			break;

		int leftPosition = values[(cursorPosition * 4) + 1];
		int rightPosition = values[(cursorPosition * 4) + 2];
		int targetPosition = values[(cursorPosition * 4) + 3];

		switch (opcode)
		{
		case 1:
			values[targetPosition] = values[leftPosition] + values[rightPosition];
			break;
		case 2:
			values[targetPosition] = values[leftPosition] * values[rightPosition];
			break;
		case 99:
			break;
		default:
			break;
		}
		cursorPosition++;
	}

	//index = 0;
	//for (auto number = values.begin(); number != values.end(); ++number) {
	//	std::cout << *number;
	//	if (index % 4 == 3) {
	//		std::cout << std::endl;
	//	}
	//	else {
	//		std::cout << " ";
	//	}
	//	index++;
	//}

	//std::cout << std::endl << std::endl << std::endl << values[0];

	std::cout << "noun: " << noun << " verb: " << verb << " => " << values[0] << std::endl;

	return values[0];
}
