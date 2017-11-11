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
	AS(int number, float connections, std::vector<std::string> ip, int customers);
	AS(int number);
	int getNum();
	float getConns();
	int getCust();
	std::vector<std::string> getIP();
	void setNum(int num);
	void setConns(float connections);
	void setIP(std::vector<std::string> ip);
	void setCust(int customers);
private:
	std::vector<std::string> ip;
	int number;
	int customers;
	float connections;
};

#endif