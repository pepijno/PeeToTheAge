#pragma once

#include <iostream>
#include <cstdlib>

#include "SecretKey.h"
#include "ProofKit.h"

class ProofKitPair
{
public:
	ProofKitPair();
	ProofKitPair(const unsigned int value, const bool greater);

	const SecretKey& getSecretKey() const { return this->secretKey; }
	const ProofKit& getProofKit() const { return this->proofKit; }

	std::string print() const;

	bool isSet() const;

private:
	ProofKit proofKit;
	SecretKey secretKey;
};
