#include "HashHelper.h"
#include "ProofKitPair.h"

ProofKitPair::ProofKitPair()
{
	this->secretKey = "0";
	this->proofKit = "0";
}

ProofKitPair::ProofKitPair(const int value)
{
	int randomInt = rand();
	std::string secret = HashHelper::SHA256HashString(std::to_string(randomInt));
	std::string proofKit = HashHelper::SHA256HashString(secret);

	for(int i = 0; i < value; ++i) {
		proofKit = HashHelper::SHA256HashString(proofKit);
	}

	this->secretKey = secret;
	this->proofKit = proofKit;
	this->value = value;
}

std::string ProofKitPair::makeProof(const int valueToProof) const
{
	if(this->value < valueToProof) {
		throw std::invalid_argument("Value of the proofkit cannot be smaller than the value to proof!");
	}

	std::string proof = HashHelper::SHA256HashString(this->secretKey);

	for(int i = 0; i < (this->value - valueToProof); ++i) {
		proof = HashHelper::SHA256HashString(proof);
	}

	return proof;
}
