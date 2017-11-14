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

	//set up for 2.3
	for (int i = 0; i < second.size(); i = i + 3) {
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

	//Set up for 2.2
	std::map<int, std::vector<std::vector<int>>> mapASWithCust; //this set holds pairs of {AS_num, Connections[[peers], [customers], [providers]]}
	for (int i = 0; i < second.size(); i = i + 3) {
		int origin = std::stoi(second.at(i));
		std::vector<std::vector<int>> originVector;
		std::vector<int> originVectorPeers;
		std::vector<int> originVectorCustomers;
		std::vector<int> originVectorProviders;

		originVector.push_back(originVectorPeers);
		originVector.push_back(originVectorCustomers);
		originVector.push_back(originVectorProviders);

		int connection = std::stoi(second.at(i + 1));
		std::vector<std::vector<int>> connectionVector;
		std::vector<int> connectionVectorPeers;
		std::vector<int> connectionVectorCustomers;
		std::vector<int> connectionVectorProviders;

		connectionVector.push_back(connectionVectorPeers);
		connectionVector.push_back(connectionVectorCustomers);
		connectionVector.push_back(connectionVectorProviders);

		int type = std::stoi(second.at(i + 2)); //0 = peer, -1 = customer
		int temp = 0;

		//time for origin input
		if (mapASWithCust.count(origin) == 0) {
			//Origin not found
			if (type == 0) {
				//connection is peer
				originVector.at(0).push_back(connection);
				mapASWithCust.insert(std::make_pair(origin, originVector));
			}
			else {
				//connection is customer
				originVector.at(1).push_back(connection);
				mapASWithCust.insert(std::make_pair(origin, originVector));
			}
		}
		else {
			//Origin found
			if (type == 0) {
				//connection is peer
				mapASWithCust.at(origin).at(0).push_back(connection);
			}
			else {
				//connection is customer
				mapASWithCust.at(origin).at(1).push_back(connection);
			}
		}

		//Now time for connections
		if (mapASWithCust.count(connection) == 0) {
			//Connection not found
			if (type == 0) {
				//Origin is peer
				connectionVector.at(0).push_back(origin);
				mapASWithCust.insert(std::make_pair(connection, connectionVector));
			}
			else {
				//Origin is provider
				connectionVector.at(2).push_back(origin);
				mapASWithCust.insert(std::make_pair(connection, connectionVector));
			}
		}
		else {
			//Connection found
			if (type == 0) {
				//Origin is peer
				mapASWithCust.at(connection).at(0).push_back(origin);
			}
			else {
				//Origin is provider
				mapASWithCust.at(connection).at(2).push_back(origin);
			}
		}
	}

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

	//2.2 p2 w/ maps try: 
	for (auto const& x : mapASWithCust) {
		int tot = x.second.at(0).size() + x.second.at(1).size() + x.second.at(2).size();
		if (tot == 1) 
			bin1++;
		else if (tot <= 5) 
			bin2++;
		else if (tot <= 100) 
			bin5++;
		else if (tot <= 200) 
			bin100++;
		else if (tot <= 1000) 
			bin200++;
		else 
			bin1000++;
		if (x.second.at(1).size() == 0 && tot <= 2) //Enterprise
			enterpriseAS++;
		else if (x.second.at(1).size() == 0 && tot > 0) //Content
			contentAS++;
		else if (x.second.at(1).size() > 0) //Transit
			transitAS++;
	}

	std::cout << "Bin 1: " << bin1 << std::endl;
	std::cout << "Bin 2-5: " << bin2 << std::endl;
	std::cout << "Bin 6-100: " << bin5 << std::endl;
	std::cout << "Bin 101-200: " << bin100 << std::endl;
	std::cout << "Bin 201-1000: " << bin200 << std::endl;
	std::cout << "Bin 1001+: " << bin1000 << std::endl;
	std::cout << "Transit " << transitAS << std::endl;
	std::cout << "Enterpise " << enterpriseAS << std::endl;
	std::cout << "Content " << contentAS << std::endl;

	//2.3
	//degree = connections + customers

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