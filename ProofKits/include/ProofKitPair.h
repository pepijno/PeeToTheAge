#pragma once

#include <iostream>
#include <cstdlib>

#include "SecretKey.h"
#include "ProofKit.h"

class ProofKitPair
{
public:
	ProofKitPair();
	ProofKitPair(const std::string proofKit, const std::string secretKey, const unsigned int value);
	ProofKitPair(const unsigned int value, const std::string secret, const bool greater);

	const SecretKey& getSecretKey() const { return this->secretKey; }
	const ProofKit& getProofKit() const { return this->proofKit; }

	std::string print() const;

	bool isSet() const;

private:
	ProofKit proofKit;
	SecretKey secretKey;
};
