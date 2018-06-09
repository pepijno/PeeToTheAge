#pragma once

#include <iostream>
#include <cstdlib>

class ProofKitPair
{
public:
	ProofKitPair();
	ProofKitPair(const int value);

	std::string getSecretKey() const { return this->secretKey; }
	std::string getProofKit() const { return this->proofKit; }
	int getValue() const { return this->value; }

	std::string makeProof(const int valueToProof) const;

	std::string print() const;

	bool isSet() const;

private:
	int value;
	std::string secretKey;
	std::string proofKit;
};
