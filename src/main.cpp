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
	//for (j = 0; j < secondAS.size(); j++) { // ip stuff
	//	if (secondAS.at(j).getNum() == 393406) {
	//		for (k = 0; k < secondAS.at(j).getConns().size(); k++) {
	//			std::cout << secondAS.at(j).getConns().at(k) << std::endl;
	//		}
	//	}
	//	for (k = 0; k < ipaddr.size(); k = k + 3) {
	//		try {
	//			if (std::stol(ipaddr.at(k + 2)) == secondAS.at(j).getNum()) {
	//				secondAS.at(j).setIP(ipaddr.at(k));
	//			}
	//		}
	//		catch (std::out_of_range& e) {
	//			//shrug
	//		}
	//	}
	//}

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
	//make a map now with degree instead of vector<int>
	std::map<int, int> mapAS_modified;
	for (auto const& x : mapAS) {
		mapAS_modified.insert(std::make_pair(x.first, x.second.size()));
	}

	//All ASs are in with their degrees, time to sort: sortedMapAS = map(Degree, AS number)
	std::multimap<int, int> sortedMapAS = flip_map(mapAS_modified);

	//Create Clique S, initialize with highest degree AS
	std::vector<int> s;
	s.push_back(sortedMapAS.rbegin()->second);
	bool done = false;

	//Now let's go through sortedMapAS, iterating from the largest degree to the smallest to find all T1
	for (auto iter = sortedMapAS.rbegin(); iter != sortedMapAS.rend(); ++iter) {
		if (iter->second == 6939) {
			continue;
		}
		for (int i = 0; i < s.size(); i++) { // loop through s now to see if each element in S is connected to our next AS
			if (std::find(mapAS.at(s.at(i)).begin(), mapAS.at(s.at(i)).end(), iter->second) != mapAS.at(s.at(i)).end()) { //element contains next one, can continue
				continue;
			}
			else {
				done = true;
				break;
			}
		}
		if (done) {
			break;
		}
		else {
			s.push_back(iter->second);
		}
	}
	std::ofstream output;
	output.open("Tier_One_AS.txt");
	output << "AS\n";


	for (int i = 0; i < s.size(); i++) {
		output << std::to_string(s.at(i)) + "\n";
	}
	output.close();
	return 0;
}