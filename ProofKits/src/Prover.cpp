#include "Prover.h"
#include "Misc.h"

Prover::Prover(const ProofKit& lowerProofKit, const ProofKit& upperProofKit, const Proof& lowerProof, const Proof& upperProof)
{
	this->lowerProofKit = lowerProofKit;
	this->upperProofKit = upperProofKit;

	this->lowerProof = lowerProof;
	this->upperProof = upperProof;
}

bool Prover::prove(const unsigned int lower, const unsigned int upper) const
{
	unsigned upp = Misc::maxValue - upper;
	bool l = this->lowerProof.proveProof(this->lowerProofKit, lower);
	bool u = this->upperProof.proveProof(this->upperProofKit, upp);

	return l && u;
}
