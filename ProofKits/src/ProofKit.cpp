#include <sstream>

#include "HashHelper.h"
#include "ProofKit.h"

ProofKit::ProofKit()
{
	this->proofKit = "";
	this->value = 0;
}

ProofKit::ProofKit(const unsigned int value, const std::string proofKit)
{
	this->proofKit = proofKit;
	this->value = value;
}

ProofKit::ProofKit(const std::string secretKey, const unsigned int value, const bool greater)
{
	std::string proofKit = HashHelper::SHA256HashString(secretKey);

	unsigned int val = value;
	if(!greater) {
		val = HashHelper::maxValue - value;
	}

	for(unsigned int i = 0; i < val; ++i) {
#ifdef _DEBUG
		std::cerr << proofKit << "\n";
#endif
		proofKit = HashHelper::SHA256HashString(proofKit);
	}
#ifdef _DEBUG
	std::cerr << proofKit << "\n\n";
#endif

	this->proofKit = proofKit;
	this->value = val;
	this->greater = greater;
}

std::string ProofKit::print() const
{
	std::stringstream ss;

	ss << "ProofKit(\n"
		<< "\tProofKit: " << this->proofKit << ",\n"
		<< "\tValue: " << this->value << ",\n"
		<< ")\n";

	return ss.str();
}

bool ProofKit::isSet() const
{
	return this->proofKit.compare("");
}
