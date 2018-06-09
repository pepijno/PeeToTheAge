#include <sstream>

#include "SecretKey.h"

SecretKey::SecretKey()
{
	this->key = "";
}

SecretKey::SecretKey(std::string secretKey)
{
	this->key = secretKey;
}

std::string SecretKey::print() const
{
	std::stringstream ss;

	ss << "SecretKey(\n"
		<< "\tkey: " << this->key << ",\n"
		<< ")\n";
	return ss.str();
}

bool SecretKey::isSet() const
{
	return this->key.compare("");
}
