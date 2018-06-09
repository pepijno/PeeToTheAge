#include <iostream>
#include <cstdlib>
#include <sstream>

#include "HashHelper.h"
#include "Proof.h"

Proof::Proof()
{
	this->proof = "";
	this->valueToProve = 0;
}

Proof::Proof(const ProofKitPair& proofKitPair, const unsigned int value)
{
	if(proofKitPair.getValue() < value) {
		throw std::invalid_argument("Value of the proofkit cannot be smaller than the value to proof!");
	}

	std::string proof = HashHelper::SHA256HashString(proofKitPair.getSecretKey());

	for(int i = 0; i < (proofKitPair.getValue() - value); ++i) {
#ifdef _DEBUG
		std::cerr << proof << "\n";
#endif
		proof = HashHelper::SHA256HashString(proof);
	}
#ifdef _DEBUG
	std::cerr << proof << "\n";
#endif

	this->proof = proof;
	this->valueToProve = value;
}

bool Proof::proveProof(const ProofKitPair& proofKitPair) const
{
	std::string prf = this->proof;
	for(int i = 0; i < this->valueToProve; ++i) {
		prf = HashHelper::SHA256HashString(prf);
#ifdef _DEBUG
		std::cerr << prf << "\n";
#endif
	}

	return !prf.compare(proofKitPair.getProofKit());
}

bool Proof::isSet() const
{
	return this->proof.compare("");
}

std::string Proof::print() const
{
	std::stringstream ss;

	ss << "Value to prove: " << this->valueToProve << "\n";
	ss << "Proof: " << this->proof << "\n";

	return ss.str();
}
