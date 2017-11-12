#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>
#include "parser.h"
#include "AS.h"

int main(void) {
	int transit = 0;
	int enterprise = 0;
	int content = 0;
	int j = 0;
	int k = 0;
	std::vector<std::string> first = partOneParse();
	std::vector<std::string> second = partTwoParse();
	std::vector<AS> secondAS;
	for (int i = 0; i < first.size(); i++) {
		if (first.at(i).find("Transit") != std::string::npos) {
			transit++;
		}
		if (first.at(i).find("Enterpise") != std::string::npos) {
			enterprise++;
		}
		if (first.at(i).find("Content") != std::string::npos) {
			content++;
		}
	}
	std::cout << "Transit " << transit << std::endl;
	std::cout << "Enterpise " << enterprise << std::endl;
	std::cout << "Content " << content << std::endl;

	for (int i = 0; i < second.size(); i = i + 3) {
		int temp = std::stoi(second.at(i));
		if (i == 0) { //idk if this if branch is needed lol
			secondAS.push_back(AS(temp));
			j = 0;
		}
		else {
			for (j = 0; j < secondAS.size(); j++) {
				if (secondAS.at(j).getNum() == temp) break;
			}
			if (j == secondAS.size()) {
				secondAS.push_back(AS(temp));
			}
		}
		if (std::stoi(second.at(i + 2)) == -1) {
			secondAS.at(j).setCust(std::stoi(second.at(i + 1)));
			secondAS.at(j).setConns(std::stoi(second.at(i + 1)));
		}
		else {
			secondAS.at(j).setConns(std::stoi(second.at(i + 1)));
		}
		//need to handle ip bullshit
	}
	for (j = 0; j < secondAS.size(); j++) {
		if (secondAS.at(j).getNum() == 42) {
			std::cout << secondAS.at(j).getCust().size() << std::endl;
			std::cout << secondAS.at(j).getConns().size() << std::endl;
		}
	}
	std::cout << secondAS.size() << std::endl;
	return 0;
}