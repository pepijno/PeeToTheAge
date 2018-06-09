#include <iostream>
#include <cstdlib>
#include <sstream>

#include "HashHelper.h"
#include "Proof.h"

Proof::Proof()
{
	this->proof = "";
}

Proof::Proof(const std::string proof)
{
	this->proof = proof;
}

Proof::Proof(const ProofKitPair& proofKitPair, const unsigned int value)
{
	if(proofKitPair.getProofKit().getValue() < value) {
		throw std::invalid_argument("Value of the proofkit cannot be smaller than the value to proof!");
	}

#ifdef _DEBUG
	std::cerr << proofKitPair.getProofKit().getValue() << "\n";
	std::cerr << value << "\n";
#endif

	std::string proof = HashHelper::SHA256HashString(proofKitPair.getSecretKey().getKey());

	for(unsigned int i = 0; i < (proofKitPair.getProofKit().getValue() - value); ++i) {
#ifdef _DEBUG
		std::cerr << proof << "\n";
#endif
		proof = HashHelper::SHA256HashString(proof);
	}
#ifdef _DEBUG
	std::cerr << proof << "\n\n";
#endif

	this->proof = proof;
}

bool Proof::proveProof(const ProofKit& proofKit, const unsigned int value) const
{
	std::string prf = this->proof;
	for(unsigned int i = 0; i < value; ++i) {
		prf = HashHelper::SHA256HashString(prf);
#ifdef _DEBUG
		std::cerr << prf << "\n";
#endif
	}

	std::cerr << "\n";

	return !prf.compare(proofKit.getProofKit());
}

bool Proof::isSet() const
{
	return this->proof.compare("");
}

std::string Proof::print() const
{
	std::stringstream ss;

	ss << "Proof(\n"
		<< "\tProof: " << this->proof << ",\n"
		<< ")\n";

	return ss.str();
}
