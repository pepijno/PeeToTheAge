#include <sstream>

#include "HashHelper.h"
#include "ProofKitPair.h"

ProofKitPair::ProofKitPair()
{
}

ProofKitPair::ProofKitPair(const std::string proofKit, const std::string secretKey, const unsigned int value)
{
	SecretKey sctKey(secretKey);
	this->secretKey = sctKey;

	ProofKit prfKit(value, proofKit);
	this->proofKit = prfKit;
}

ProofKitPair::ProofKitPair(const unsigned int value, const std::string secret, const bool greater)
{
	SecretKey secretKey(secret);
	this->secretKey = secretKey;

	ProofKit proofKit(this->secretKey.getKey(), value, greater);
	this->proofKit = proofKit;
}

std::string ProofKitPair::print() const
{
	std::stringstream ss;

	ss << "ProofKitPair(\n"
		<< this->proofKit.print()
		<< this->secretKey.print()
		<< ")\n";

	return ss.str();
}

bool ProofKitPair::isSet() const
{
	return this->secretKey.isSet() && this->proofKit.isSet();
}
