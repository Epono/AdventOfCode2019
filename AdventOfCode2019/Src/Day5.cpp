#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "Day5.hpp"

int runIntcodeComputer(std::vector<int> &values);

void day5() {
	std::ifstream inputFile("Data/Day5.txt");
	std::string line;
	std::getline(inputFile, line);

	std::vector<std::string> strings;
	boost::split(strings, line, boost::is_any_of(","), boost::token_compress_on);

	std::vector<int> numbersOriginal;

	//std::transform(strings.begin(), strings.end(), std::back_inserter(numbers), [](const std::string& str) { return std::stoi(str); });
	std::transform(strings.begin(), strings.end(), std::back_inserter(numbersOriginal), &boost::lexical_cast<int, std::string>);

	// Reliquat, je garde lol
	std::vector<int> numbers(numbersOriginal.size());
	std::copy(numbersOriginal.begin(), numbersOriginal.end(), numbers.begin());

	int result = runIntcodeComputer(numbers);

}

int runIntcodeComputer(std::vector<int> &values) {
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
	while (true) {
		// Extract opcode and parameters
		int code = values[cursorPosition];
		int opcode = code % 100;

		int parametersValue = code / 100;
		std::vector<bool> parametersMode(3, 0);
		for (int i = 0; parametersValue > 0; i++) {
			parametersMode[i] = parametersValue % 10 == 1;
			parametersValue /= 10;
		}

		// Halt condition
		if (opcode == 99)
			break;

		
		int cursorIncrement = 0;
		switch (opcode)
		{
		case 1:
		case 2:
		{
			// Add
			int valueAtAddress1 = values[cursorPosition + 1];
			int value1 = parametersMode[0] ? valueAtAddress1 : values[valueAtAddress1];

			int valueAtAddress2 = values[cursorPosition + 2];
			int value2 = parametersMode[1] ? valueAtAddress2 : values[valueAtAddress2];

			int valueAtAddressTarget = values[cursorPosition + 3];

			if (opcode == 1) {
				values[valueAtAddressTarget] = value1 + value2;
			}
			else {
				values[valueAtAddressTarget] = value1 * value2;
			}
			
			cursorIncrement = 4;
			break;
		}
		case 3:
		{
			// Input
			int inputValue = 0;
			std::cout << "Enter value :" << std::endl;
			std::cin >> inputValue;
			std::cout << "Thanks!" << std::endl << std::endl;

			int addressTarget = values[cursorPosition + 1];
			values[addressTarget] = inputValue;

			cursorIncrement = 2;
			break;
		}
		case 4:
		{
			// Output
			int addressTarget = values[cursorPosition + 1];
			int targetValue = values[addressTarget];

			std::cout << "Output is: " << targetValue << std::endl << std::endl;

			cursorIncrement = 2;
			break;
		}
		case 5:
		case 6:
		{
			int valueAtAddress1 = values[cursorPosition + 1];
			int value1 = parametersMode[0] ? valueAtAddress1 : values[valueAtAddress1];

			int valueAtAddress2 = values[cursorPosition + 2];
			int value2 = parametersMode[1] ? valueAtAddress2 : values[valueAtAddress2];

			if (opcode == 5 && value1 != 0 || opcode == 6 && value1 == 0) {
				cursorPosition = value2;
				cursorIncrement = 0;
			}
			else {
				cursorIncrement = 3;
			}
			break;
		}
		case 7:
		case 8:
		{
			// Add
			int valueAtAddress1 = values[cursorPosition + 1];
			int value1 = parametersMode[0] ? valueAtAddress1 : values[valueAtAddress1];

			int valueAtAddress2 = values[cursorPosition + 2];
			int value2 = parametersMode[1] ? valueAtAddress2 : values[valueAtAddress2];

			int valueAtAddressTarget = values[cursorPosition + 3];

			if ( (opcode == 7 && value1 < value2) || (opcode == 8 && value1 == value2)) {
				values[valueAtAddressTarget] = 1;
			}
			else {
				values[valueAtAddressTarget] = 0;
			}

			cursorIncrement = 4;
			break;
		}
		}
		cursorPosition += cursorIncrement;
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

	std::cout << "Value at 0: " << values[0] << std::endl;

	return values[0];
}
