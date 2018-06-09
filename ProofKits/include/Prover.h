#pragma once

#include <iostream>
#include <cstdlib>

#include "ProofKit.h"
#include "Proof.h"

class Prover
{
public:
	Prover(const ProofKit& lowerProofKit, const ProofKit& upperProofKit, const Proof& lowerProof, const Proof& upperProof);
	bool prove(const unsigned int lower, const unsigned int upper) const;
private:
	ProofKit lowerProofKit;
	ProofKit upperProofKit;
	Proof lowerProof;
	Proof upperProof;
};
