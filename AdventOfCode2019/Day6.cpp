#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "Day6.hpp"

void day6() {
	std::ifstream inputFile("Day6.txt");
	std::string line;
	std::vector<std::string> strings;
	std::map<std::string, std::string> map;
	const std::string CENTER_OF_MASS = "COM";
	const std::string YOU = "YOU";
	const std::string SANTA = "SAN";

	while (inputFile >> line) {
		//DES)SRC
		std::vector<std::string> numbersStr;
		boost::split(numbersStr, line, boost::is_any_of(")"), boost::token_compress_on);

		// Cheating
		std::string dest(numbersStr[0]);
		std::string src(numbersStr[1]);

		map[src] = dest;

		std::cout << "SRC: " << src << " - DEST: " << dest << std::endl;
	}

	int countOfDirectOrbits = 0;
	int countOfIndirectOrbits = 0;

	// For each planet
	for (std::map<std::string, std::string>::iterator it = map.begin(); it != map.end(); ++it) {
		countOfDirectOrbits++;

		//std::string tempDest = map[it->first];
		//std::map<std::string, std::string>::iterator itTemp = it;
		//std::pair<std::string, std::string> tempPair = make_pair(it->first, it->second);
		std::string tempDest = it->second;

		// For each indirect orbit of that planet, until COM
		while (tempDest != CENTER_OF_MASS) {
			tempDest = map[tempDest];
			
			countOfIndirectOrbits++;
		}
	}
	std::string commonAncestor("");

	std::vector<std::string> pathFromYOUtoCOM;
	int stepsFromYOUtoCommonAncestor = 0;
	{
		std::string tempDest = map[YOU];

		// For each indirect orbit of that planet, until COM
		while (tempDest != CENTER_OF_MASS) {
			tempDest = map[tempDest];
			pathFromYOUtoCOM.push_back(tempDest);
		}
	}
	std::cout << "Path from YOU to COM: " << std::endl;
	for (auto i = pathFromYOUtoCOM.begin(); i != pathFromYOUtoCOM.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl << std::endl;

	std::vector<std::string> pathFromSANtoCOM;
	int stepsFromSANTAtoCommonAncestor = 1;
	{
		std::string tempDest = map[SANTA];

		// For each indirect orbit of that planet, until COM
		while (tempDest != CENTER_OF_MASS) {
			tempDest = map[tempDest];
			pathFromSANtoCOM.push_back(tempDest);
			
			if (commonAncestor == "") {
				auto t = std::find(pathFromYOUtoCOM.begin(), pathFromYOUtoCOM.end(), tempDest);
				if (t != pathFromYOUtoCOM.end()) {
					// found
					commonAncestor = tempDest;
				}
				else {
					stepsFromSANTAtoCommonAncestor++;
				}
			}
		}
	}
	std::cout << "Path from YOU to COM: " << std::endl;
	for (auto i = pathFromSANtoCOM.begin(); i != pathFromSANtoCOM.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl << std::endl;

	std::cout << commonAncestor << std::endl;

	// Steps from YOU to common ancestor
	std::vector<std::string>::iterator it = std::find(pathFromYOUtoCOM.begin(), pathFromYOUtoCOM.end(), commonAncestor);
	stepsFromYOUtoCommonAncestor = std::distance(pathFromYOUtoCOM.begin(), it) + 1;

	std::cout << "Steps from SANTA to common ancestor: " << stepsFromSANTAtoCommonAncestor << std::endl;
	std::cout << "Steps from YOU to common ancestor: " << stepsFromYOUtoCommonAncestor << std::endl;





	std::cout << (countOfDirectOrbits + countOfIndirectOrbits) << std::endl;
}