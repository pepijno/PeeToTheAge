#include "RangeProof.h"
#include "HashHelper.h"
#include "Misc.h"

RangeProof::RangeProof()
{
}

RangeProof::RangeProof(const std::string lowerProofKit, const std::string upperProofKit, const std::string secretKey, const unsigned int value)
{
	ProofKitPair proofKitPair(lowerProofKit, secretKey, value);
	this->lowerProofKitPair = proofKitPair;

	unsigned int val = Misc::maxValue - value;

	ProofKitPair prfKitPair(upperProofKit, secretKey, val);
	this->upperProofKitPair = prfKitPair;

#ifdef _DEBUG
	std::cerr << this->lowerProofKitPair.print() << "\n"
		<< this->upperProofKitPair.print() << "\n";
#endif
}

RangeProof::RangeProof(const unsigned int value)
{
	unsigned int randomInt = rand();
	std::string secret = HashHelper::SHA256HashString(std::to_string(randomInt));

	ProofKitPair proofKitPair(value, secret, true);
	this->lowerProofKitPair = proofKitPair;

	int val = Misc::maxValue - value;

	ProofKitPair prfKitPair(val, secret, true);
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
