#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <map>
#include <set>
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
	//std::vector<std::string> ipaddr = ipAddrParse();
	std::vector<AS> secondAS;
	std::map<int, std::vector<int>> mapAS; //this set holds pairs of {AS_num, Connections(includes customers)}
	int bin1 = 0;
	int bin2 = 0;
	int bin5 = 0;
	int bin100 = 0;
	int bin200 = 0;
	int bin1000 = 0;
	int transitAS = 0;
	int enterpriseAS = 0;
	int contentAS = 0;
	//2.1
	
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

	//2.2
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
			int t1 = std::stoi(second.at(i + 1));
			for (k = 0; k < secondAS.size(); k++) {
				if (secondAS.at(k).getNum() == t1) break;
			}
			if (k == secondAS.size()) {
				secondAS.push_back(AS(t1));
			}
			secondAS.at(k).setConns(std::stoi(second.at(i)));
		}
	}
	for (j = 0; j < secondAS.size(); j++) {
		/*if (secondAS.at(j).getNum() == 393406) {
			for (k = 0; k < secondAS.at(j).getConns().size(); k++) {
				std::cout << secondAS.at(j).getConns().at(k) << std::endl;
			}
		}*/
		int tot = secondAS.at(j).getConns().size() + secondAS.at(j).getCust().size();
		if (tot == 1) bin1++;
		else if (tot <= 5) bin2++;
		else if (tot <= 100) bin5++;
		else if (tot <= 200) bin100++;
		else if (tot <= 1000) bin200++;
		else bin1000++;
		if (secondAS.at(j).getCust().size() == 0 &&  tot <= 2) enterpriseAS++;
		else if (secondAS.at(j).getCust().size() == 0 && tot > 0) contentAS++;
		else if (secondAS.at(j).getCust().size() > 0) transitAS++;
		/*for (k = 0; k < ipaddr.size(); k = k + 3) {
			try {
				if (std::stol(ipaddr.at(k + 2)) == secondAS.at(j).getNum()) {
					secondAS.at(j).setIP(ipaddr.at(k));
				}
			}
			catch (std::out_of_range& e) {
				//shrug
			}
		}*/
	}
	std::cout << bin1 << std::endl;
	std::cout << bin2 << std::endl;
	std::cout << bin5 << std::endl;
	std::cout << bin100 << std::endl;
	std::cout << bin200 << std::endl;
	std::cout << bin1000 << std::endl;
	std::cout << "Transit " << transitAS << std::endl;
	std::cout << "Enterpise " << enterpriseAS << std::endl;
	std::cout << "Content " << contentAS << std::endl;

	//2.3
	//degree = connections + customers

	for (int i = 0; i < second.size(); i=i+3) {
		int origin = std::stoi(second.at(i));
		std::vector<int> originVector;
		originVector.push_back(origin);
		int connection = std::stoi(second.at(i + 1));
		std::vector<int> connectionVector;
		connectionVector.push_back(connection);
		int type = std::stoi(second.at(i + 2)); //0 = peer, -1 = customer
		int temp = 0;

		if (mapAS.count(origin) == 0) {//Origin not found
			mapAS.insert(std::make_pair(origin, connectionVector));
		}
		else {//Origin found
			mapAS.at(origin).push_back(connection);
		}

		if (mapAS.count(connection) == 0) {//Connection not found
			mapAS.insert(std::make_pair(connection, originVector));
		}
		else {//Connection found
			mapAS.at(connection).push_back(origin);
		}
	}

	std::ofstream output;
	output.open("out3.txt");
	output << "AS\tDegree";
	for (auto const& x : mapAS) {
		output << std::to_string(x.first) + "\t" + std::to_string(x.second.size()) + "\n";
	}
	output.close();

	//2.4 goes below here
	return 0;
}

// for 2.3, inspiration from stack overflow
template<typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B> &p)
{
	return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B, A> flip_map(const std::map<A, B> &src)
{
	std::multimap<B, A> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
		flip_pair<A, B>);
	return dst;
}