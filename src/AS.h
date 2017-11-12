#ifndef AS_H
#define AS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

class AS {
public:
	AS();
	AS(int number, int connections, std::vector<std::string> ip, int customers);
	AS(int number);
	int getNum();
	std::vector<int> getConns();
	std::vector<int> getCust();
	std::vector<std::string> getIP();
	void setNum(int num);
	void setConns(int connections);
	void setIP(std::vector<std::string> ip);
	void setCust(int customers);
private:
	std::vector<std::string> ip;
	int number;
	std::vector<int> customers;
	std::vector<int> connections;
};

#endif