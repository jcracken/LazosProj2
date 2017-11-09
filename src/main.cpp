#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>
#include "parser.h"

int main(void) {
	int transit = 0;
	int enterprise = 0;
	int content = 0;
	std::vector<std::string> first = partOneParse();
	for (int i = 0; i < first.size(); i++) {
		if (first.at(i).find("Transit") != std::string::npos) {
			transit++;
		}
		if (first.at(i).find("Enterprise") != std::string::npos) {
			enterprise++;
		}
		if (first.at(i).find("Content") != std::string::npos) {
			content++;
		}
	}
	std::cout << "Transit " << transit << std::endl;
	std::cout << "Enterprise " << enterprise << std::endl;
	std::cout << "Content " << content << std::endl;
}