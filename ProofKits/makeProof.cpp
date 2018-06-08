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


std::string generateProof(const std::string secret, const int value, const int toProof)
{
	if(value < toProof) {
		throw std::invalid_argument( "Value cannot be smaller than toProof" );
	}

	std::string proof = SHA256HashString(secret);

	for(int i = 0; i < (value - toProof); ++i) {
		proof = SHA256HashString(proof);
	}

	return proof;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	if(argc != 4) {
		throw std::invalid_argument( "Provide exactly three parameters (proofKit, value and value to proof) to generate a proof " );
	}

	std::string secretKey = argv[1];
	unsigned int value = std::atoi(argv[2]);
	unsigned int toProof = std::atoi(argv[3]);

	std::string proof = generateProof(secretKey, value, toProof);

	std::cout << proof << std::endl;
}
