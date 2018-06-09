#pragma once

#include <iostream>
#include <cstdlib>

#include "ProofKitPair.h"
#include "Proof.h"

class RangeProof
{
public:
	RangeProof();
	RangeProof(const std::string lowerProofKit, const std::string upperProofKit, const std::string secretKey, const unsigned int value);
	RangeProof(const unsigned int value);

	const ProofKit& getLowerProofKit() { return this->lowerProofKitPair.getProofKit(); }
	const ProofKit& getUpperProofKit() { return this->upperProofKitPair.getProofKit(); }
	const Proof& getLowerProof() { return this->lowerProof; }
	const Proof& getUpperProof() { return this->upperProof; }

	void generateProof(const unsigned int lowerBound, const unsigned int upperBound);
protected:
	ProofKitPair lowerProofKitPair;
	ProofKitPair upperProofKitPair;
	Proof upperProof;
	Proof lowerProof;
};
