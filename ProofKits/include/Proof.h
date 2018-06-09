#pragma once

#include <iostream>
#include <cstdlib>

#include "ProofKitPair.h"
#include "ProofKit.h"

class Proof
{
public:
	Proof();
	Proof(const std::string proof);
	Proof(const ProofKitPair& proofKitPair, const unsigned int value);

	std::string getProof() const { return this->proof; }

	bool proveProof(const ProofKit& proofKit, const unsigned int value) const;

	bool isSet() const;

	std::string print() const;

private:
	std::string proof;
};
