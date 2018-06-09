#pragma once

#include <iostream>
#include <cstdlib>

#include "ProofKitPair.h"

class Proof
{
public:
	Proof();
	Proof(const ProofKitPair& proofKitPair, const unsigned int value);

	std::string getProof() const { return this->proof; }
	unsigned int getValueToProve() const { return this->valueToProve; }

	bool proveProof(const ProofKitPair& proofKitPair) const;

	bool isSet() const;

	std::string print() const;

private:
	std::string proof;
	unsigned int valueToProve;
};
