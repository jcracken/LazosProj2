#include "parser.h"

std::vector<std::string> partOneParse() {
	std::ifstream inFS;
	std::string line;
	std::vector<std::string> result;
	std::string delimiter = "|";
	inFS.open("first.txt");
	if (!inFS.is_open()) { //check opened correctly
		std::cout << "Could not open input file." << std::endl;
		exit(EXIT_FAILURE);
	}
	while(!inFS.eof()) {
		getline(inFS, line);
		result.push_back(line.substr(0, line.find(delimiter)));
		line.erase(0, line.find(delimiter) + delimiter.length());
		result.push_back(line.substr(0, line.find(delimiter)));
		line.erase(0, line.find(delimiter) + delimiter.length());
		result.push_back(line.substr(0, line.find(delimiter)));
	}
	return result;
}

std::vector<std::string> partTwoParse() {
	std::ifstream inFS;
	std::string line;
	std::vector<std::string> result;
	std::string delimiter = "|";
	inFS.open("second.txt");
	if (!inFS.is_open()) { //check opened correctly
		std::cout << "Could not open input file." << std::endl;
		exit(EXIT_FAILURE);
	}
	while (!inFS.eof()) {
		getline(inFS, line);
		result.push_back(line.substr(0, line.find(delimiter)));
		line.erase(0, line.find(delimiter) + delimiter.length());
		result.push_back(line.substr(0, line.find(delimiter)));
		line.erase(0, line.find(delimiter) + delimiter.length());
		result.push_back(line.substr(0, line.find(delimiter)));
	}
	return result;
}

std::vector<std::string> ipAddrParse() {
	std::ifstream inFS;
	std::string line;
	std::vector<std::string> result;
	std::string delimiter = "\t";
	inFS.open("ipaddr.txt");
	if (!inFS.is_open()) { //check opened correctly
		std::cout << "Could not open input file." << std::endl;
		exit(EXIT_FAILURE);
	}
	while (!inFS.eof()) {
		getline(inFS, line);
		result.push_back(line.substr(0, line.find(delimiter)));
		line.erase(0, line.find(delimiter) + delimiter.length());
		result.push_back(line.substr(0, line.find(delimiter)));
		line.erase(0, line.find(delimiter) + delimiter.length());
		result.push_back(line.substr(0, line.find(delimiter)));
	}
	return result;
}