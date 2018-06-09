#include <sstream>

#include "HashHelper.h"
#include "ProofKitPair.h"

ProofKitPair::ProofKitPair()
{
	this->secretKey = "0";
	this->proofKit = "0";
}

ProofKitPair::ProofKitPair(const unsigned int value)
{
	unsigned int randomInt = rand();
	std::string secret = HashHelper::SHA256HashString(std::to_string(randomInt));
	std::string proofKit = HashHelper::SHA256HashString(secret);

	for(unsigned int i = 0; i < value; ++i) {
#ifdef _DEBUG
		std::cerr << proofKit << "\n";
#endif
		proofKit = HashHelper::SHA256HashString(proofKit);
	}
#ifdef _DEBUG
	std::cerr << proofKit << "\n";
#endif

	this->secretKey = secret;
	this->proofKit = proofKit;
	this->value = value;
}

std::string ProofKitPair::print() const
{
	std::stringstream ss;

	ss << "Secret Key: " << this->secretKey << std::endl << "ProofKit: " << this->proofKit << std::endl;

	return ss.str();
}

bool ProofKitPair::isSet() const
{
	return this->secretKey.compare("0") && this->proofKit.compare("0");
}
