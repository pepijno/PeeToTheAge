#include <iostream>
#include <cstdlib>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <crypto++/base64.h>

std::string SHA256HashString(std::string aString)
{
	std::string digest;
	CryptoPP::SHA256 hash;

	CryptoPP::StringSource foo(aString, true,
			new CryptoPP::HashFilter(hash,
				new CryptoPP::Base64Encoder (
					new CryptoPP::StringSink(digest), false)));

	return digest;
}


bool checkProof(const std::string proofKit, const std::string proof, const int toProof)
{
	std::string prf = proof;

	for(int i = 0; i < toProof; ++i) {
		prf = SHA256HashString(prf);
	}

	return !prf.compare(proofKit);
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	if(argc != 4) {
		throw std::invalid_argument( "Provide exactly three parameters (proofKit, proof and value to proof) to generate a proof " );
	}

	std::string proofKit = argv[1];
	std::string proof = argv[2];
	unsigned int toProof = std::atoi(argv[3]);

	bool isProven = checkProof(proofKit, proof, toProof);

	std::cout << isProven << std::endl;
}
