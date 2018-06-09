#pragma once

#include <iostream>
#include <cstdlib>

class ProofKit
{
public:
	ProofKit();
	ProofKit(const unsigned int value, const std::string proofKit);
	ProofKit(const std::string secretKey, const unsigned int value, const bool greater = true);

	unsigned int getValue() const { return this->value; }
	std::string  getProofKit() const { return this->proofKit; }
	bool getGreater() const { return this->greater; }

	std::string print() const;

	bool isSet() const;
private:
	bool greater;
	unsigned int value;
	std::string proofKit;
};
