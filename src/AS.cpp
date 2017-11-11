#include "AS.h"

AS::AS() {
	return;
}

AS::AS(int number, float connections, std::vector<std::string> ip, int customers) {
	this->number = number;
	this->connections = connections;
	this->ip = ip;
	this->customers = customers;
	return;
}

AS::AS(int number) {
	this->number = number;
	this->connections = 0;
	this->customers = 0;
	return;
}

int AS::getNum() {
	return this->number;
}

float AS::getConns() {
	return this->connections;
}

int AS::getCust() {
	return this->customers;
}

std::vector<std::string> AS::getIP() {
	return this->ip;
}

void AS::setNum(int num) {
	this->number = num;
	return;
}

void AS::setConns(float connections) {
	this->connections = connections;
	return;
}

void AS::setIP(std::vector<std::string> ip) {
	this->ip = ip;
	return;
}

void AS::setCust(int customers) {
	this->customers = customers;
	return;
}