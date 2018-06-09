#pragma once

#include <iostream>
#include <cstdlib>

class ProofKitPair
{
public:
	ProofKitPair();
	ProofKitPair(const unsigned int value);

	std::string getSecretKey() const { return this->secretKey; }
	std::string getProofKit() const { return this->proofKit; }
	int getValue() const { return this->value; }

	std::string print() const;

	bool isSet() const;

private:
	unsigned int value;
	std::string secretKey;
	std::string proofKit;
};
