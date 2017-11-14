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

/*int countCust(int num, std::vector<AS> secondAS) {
	int temp = 0;
	for (int i = 0; i < secondAS.size(); i++) {
		if (secondAS.at(i).getNum() == num) {
			if (secondAS.at(i).getCust().size() > 0) {
				for (int j = 0; j < secondAS.at(j).getCust().size(); j++) {
					temp = temp + countCust(secondAS.at(i).getCust().at(j), secondAS);
				}
			}
			return temp + secondAS.at(i).getCust().size();
		}
	}
}*/

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
	int temp = 0;
	std::vector<std::string> first = partOneParse();
	std::vector<std::string> second = partTwoParse();
	std::vector<std::string> ipaddr = ipAddrParse();
	std::vector<std::string> four;
	std::vector<AS> secondAS;
	std::vector<int> topAS;
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
	int classA = 0;
	int classB = 0;
	int classC = 0;
	int classD = 0;
	int classE = 0;
	int unknownAS = 0;

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

	std::map<long long, std::vector<std::string>> mapASWithIP; //this set holds pairs of {AS_num, IP Strings}
	for (int i = 0; i < ipaddr.size(); i = i + 3) {
		if (ipaddr.at(i + 2).find('_') != std::string::npos) {
			std::string s = ipaddr.at(i + 2);
			std::vector<std::string> nodeList;
			auto start = 0;
			auto end = s.find('_');
			while (end != std::string::npos)
			{
				nodeList.push_back(s.substr(start, end - start));
				start = end + 1;
				end = s.find('_', start);
			}
			for (int j = 0; j < nodeList.size(); j++) {
				long long origin = std::stoll(nodeList.at(j));
				std::string ip = ipaddr.at(i);
				std::vector<std::string> ipAddr;

				//time for origin input
				if (mapASWithIP.count(origin) == 0) {
					//Origin not found
					ipAddr.push_back(ip);
					mapASWithIP.insert(std::make_pair(origin, ipAddr));
				}
				else {
					//Origin found
					mapASWithIP.at(origin).push_back(ip);
				}
			}
		}
		else {
			long long origin = std::stoll(ipaddr.at(i + 2));

			std::string ip = ipaddr.at(i);
			std::vector<std::string> ipAddr;

			//time for origin input
			if (mapASWithIP.count(origin) == 0) {
				//Origin not found
				ipAddr.push_back(ip);
				mapASWithIP.insert(std::make_pair(origin, ipAddr));
			}
			else {
				//Origin found
				mapASWithIP.at(origin).push_back(ip);
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
	std::cout << "Content " << content << std::endl << std::endl;

	//2.2
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
		if (x.second.at(1).size() > 0) //Transit
			transitAS++;
		else if (x.second.at(1).size() == 0 && tot <= 2 && x.second.at(0).size() == 0) //Enterprise
			enterpriseAS++;
		else if (x.second.at(1).size() == 0 && x.second.at(0).size() > 0) //Content
			contentAS++;
		else
			unknownAS++;
	}
	for (auto const& x : mapASWithIP) {
		bool cA = true;
		bool cB = true;
		bool cC = true;
		bool cD = true;
		bool cE = true;
		for (int i = 0; i < x.second.size(); i++) {
			std::string s = x.second.at(i);
			std::vector<std::string> nodeList;
			auto start = 0;
			auto end = s.find('.');
			while (end != std::string::npos)
			{
				nodeList.push_back(s.substr(start, end - start));
				start = end + 1;
				end = s.find('.', start);
			}
			if (std::stoi(nodeList.at(0)) <= 127 && cA) {
				classA++;
				cA = false;
			}
			else if (std::stoi(nodeList.at(0)) <= 191 && cB) {
				classB++;
				cB = false;
			}
			else if (std::stoi(nodeList.at(0)) <= 223 && cC) {
				classC++;
				cC = false;
			}
			else if (std::stoi(nodeList.at(0)) <= 239 && cD) {
				classD++;
				cD = false;
			}
			else if (std::stoi(nodeList.at(0)) <= 255 && cE) {
				classE++;
				cE = false;
			}
		}
	}

	std::cout << "Bin 1: " << bin1 << std::endl;
	std::cout << "Bin 2-5: " << bin2 << std::endl;
	std::cout << "Bin 6-100: " << bin5 << std::endl;
	std::cout << "Bin 101-200: " << bin100 << std::endl;
	std::cout << "Bin 201-1000: " << bin200 << std::endl;
	std::cout << "Bin 1001+: " << bin1000 << std::endl << std::endl;
	std::cout << "Transit " << transitAS << std::endl;
	std::cout << "Enterpise " << enterpriseAS << std::endl;
	std::cout << "Content " << contentAS << std::endl;
	std::cout << "Unknown " << unknownAS << std::endl << std::endl;
	std::cout << "Class A: " << classA << std::endl;
	std::cout << "Class B: " << classB << std::endl;
	std::cout << "Class C: " << classC << std::endl;
	std::cout << "Class D: " << classD << std::endl;
	std::cout << "Class E: " << classE << std::endl;
	

	//2.3
	//degree = connections + customers

	//std::ofstream output;
	//output.open("out3.txt");
	//output << "AS\tDegree\n";

	//std::map<int, int> inputMap;
	//for (auto const& x : mapAS) {
	//	inputMap.insert(std::make_pair(x.first, x.second.size()));
	//}

	//std::multimap<int, int> sorted = flip_map(inputMap);
	//for (auto const& x : sorted) {
	//	output << std::to_string(x.second) + "\t" + std::to_string(x.first) + "\n";
	//}
	//output.close();

	//2.4
	/*for (int i = 0; i < secondAS.size(); i++) {
		if (secondAS.at(i).getCust().size() > 0) {
			for (int j = 0; j < secondAS.at(i).getCust().size(); j++) {
				temp = countCust(secondAS.at(i).getCust().at(j), secondAS);
			}
			temp = temp + secondAS.at(i).getCust().size();
		}
		if (topAS.size() < 15) {
			topAS.push_back(secondAS.at(i).getNum());
			std::sort(topAS.begin(), topAS.end());
		}
		else {
			for (int i = 0; i < 15; i++) {
				if (temp > topAS.at(i)) {
					topAS.insert(topAS.begin() + i, temp);
					topAS.pop_back();
				}
			}
		}
	}
	std::cout << "2.4" << std::endl;
	for (int i = 0; i < 15; i++) {
		std::cout << topAS.at(i) << std::endl;
	}*/
	return 0;
}

