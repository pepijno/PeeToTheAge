#pragma once

#include <iostream>
#include <cstdlib>

class SecretKey
{
public:
	SecretKey();
	SecretKey(std::string secretKey);

	std::string getKey() const { return this->key; }

	std::string print() const;

	bool isSet() const;
private:
	std::string key;
};
