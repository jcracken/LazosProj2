#include "AS.h"

AS::AS() {
	return;
}

AS::AS(int number, int connections, std::vector<std::string> ip, int customers) {
	this->number = number;
	this->connections.push_back(connections);
	this->ip = ip;
	this->customers.push_back(connections);
	return;
}

AS::AS(int number) {
	this->number = number;
	return;
}

int AS::getNum() {
	return this->number;
}

std::vector<int> AS::getConns() {
	return this->connections;
}

std::vector<int> AS::getCust() {
	return this->customers;
}

std::vector<std::string> AS::getIP() {
	return this->ip;
}

void AS::setNum(int num) {
	this->number = num;
	return;
}

void AS::setConns(int connections) {
	this->connections.push_back(connections);
	return;
}

void AS::setIP(std::string ip) {
	this->ip.push_back(ip);
	return;
}

void AS::setCust(int customers) {
	this->customers.push_back(customers);
	return;
}