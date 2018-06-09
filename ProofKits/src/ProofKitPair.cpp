#include <sstream>

#include "HashHelper.h"
#include "ProofKitPair.h"

ProofKitPair::ProofKitPair()
{
}

ProofKitPair::ProofKitPair(const unsigned int value, const bool greater)
{
	unsigned int randomInt = rand();
	std::string secret = HashHelper::SHA256HashString(std::to_string(randomInt));

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
