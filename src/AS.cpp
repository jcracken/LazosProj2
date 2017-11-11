#include "AS.h"

AS::AS() {
	return;
}

AS::AS(int number, int connections, std::vector<std::string> ip) {
	this->number = number;
	this->connections = connections;
	this->ip = ip;
	return;
}

AS::AS(int number) {
	this->number = number;
	return;
}

int AS::getNum() {
	return this->number;
}

int AS::getConns() {
	return this->connections;
}

std::vector<std::string> AS::getIP() {
	return this->ip;
}

void AS::setNum(int num) {
	this->number = num;
	return;
}

void AS::setConns(int connections) {
	this->connections = connections;
	return;
}

void AS::setIP(std::vector<std::string> ip) {
	this->ip = ip;
	return;
}