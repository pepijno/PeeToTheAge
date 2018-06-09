#include "RangeProof.h"
#include "Misc.h"

RangeProof::RangeProof()
{
}

RangeProof::RangeProof(const unsigned int value)
{
	ProofKitPair proofKitPair(value, true);
	this->lowerProofKitPair = proofKitPair;

	int val = Misc::maxValue - value;

	ProofKitPair prfKitPair(val, true);
	this->upperProofKitPair = prfKitPair;

#ifdef _DEBUG
	std::cerr << this->lowerProofKitPair.print() << "\n"
		<< this->upperProofKitPair.print() << "\n";
#endif
}

void RangeProof::generateProof(const unsigned int lowerBound, const unsigned int upperBound)
{
	Proof proof(this->lowerProofKitPair, lowerBound);
	this->lowerProof = proof;

	int val = Misc::maxValue - upperBound;

	Proof prf(this->upperProofKitPair, val);
	this->upperProof = prf;
}