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
	AS(int number, int connections, std::vector<std::string> ip);
	AS(int number);
	int getNum();
	int getConns();
	std::vector<std::string> getIP();
	void setNum(int num);
	void setConns(int connections);
	void setIP(std::vector<std::string> ip);
private:
	std::vector<std::string> ip;
	int number;
	int connections;
};

#endif AS_H