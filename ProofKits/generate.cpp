#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/base64.h>
#include <crypto++/files.h>

/*void GenKeyPair()
{
	// InvertibleRSAFunction is used directly only because the private key
	// won't actually be used to perform any cryptographic operation;
	// otherwise, an appropriate typedef'ed type from rsa.h would have been used.
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::InvertibleRSAFunction privkey;
	privkey.Initialize(rng, 1024);

	std::string digest;

	// With the current version of Crypto++, MessageEnd() needs to be called
	// explicitly because Base64Encoder doesn't flush its buffer on destruction.
	CryptoPP::Base64Encoder privkeysink(new CryptoPP::StringSink(digest));
	privkey.DEREncode(privkeysink);
	privkeysink.MessageEnd();

	std::cout << digest << std::endl;

	// Suppose we want to store the public key separately,
	// possibly because we will be sending the public key to a third party.
	CryptoPP::RSAFunction pubkey(privkey);

	CryptoPP::Base64Encoder pubkeysink(new CryptoPP::FileSink("pubkey.txt"));
	pubkey.DEREncode(pubkeysink);
	pubkeysink.MessageEnd();

}

void Sign()
{
	std::string strContents = "A message to be signed";
	//FileSource("tobesigned.dat", true, new StringSink(strContents));

	CryptoPP::AutoSeededRandomPool rng;

	//Read private key
	CryptoPP::ByteQueue bytes;
	CryptoPP::FileSource file("privkey.txt", true, new CryptoPP::Base64Decoder);
	file.TransferTo(bytes);
	bytes.MessageEnd();
	CryptoPP::RSA::PrivateKey privateKey;
	privateKey.Load(bytes);

	//Sign message
	CryptoPP::RSASSA_PKCS1v15_SHA_Signer privkey(privateKey);
	CryptoPP::SecByteBlock sbbSignature(privkey.SignatureLength());
	privkey.SignMessage(
		rng,
		(byte const*) strContents.data(),
		strContents.size(),
		sbbSignature);

	//Save result
	CryptoPP::FileSink sink("signed.dat");
	sink.Put((byte const*) strContents.data(), strContents.size());
	CryptoPP::FileSink sinksig("sig.dat");
	sinksig.Put(sbbSignature, sbbSignature.size());
}*/

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

class ProofKitPair
{
public:
	ProofKitPair(const int value);

	const std::string getSecretKey() { return this->secretKey; }
	const std::string getProofKit() { return this->proofKit; }
	const int getValue() { return this->value; }

	const std::string makeProof(const int valueToProof);

	const std::string print();

private:
	int value;
	std::string secretKey;
	std::string proofKit;
};

ProofKitPair::ProofKitPair(const int value)
{
	int randomInt = rand();
	std::string secret = SHA256HashString(std::to_string(randomInt));
	std::string proofKit = SHA256HashString(secret);

	for(int i = 0; i < value; ++i) {
		proofKit = SHA256HashString(proofKit);
	}

	this->secretKey = secret;
	this->proofKit = proofKit;
}

const std::string ProofKitPair::makeProof(const int valueToProof)
{
	if(this->value < valueToProof) {
		throw std::invalid_argument("Value of the proofkit cannot be smaller than the value to proof!");
	}

	std::string proof = SHA256HashString(this->secretKey);

	for(int i = 0; i < (this->value - valueToProof); ++i) {
		proof = SHA256HashString(this->secretKey);
	}

	return proof;
}

const bool checkProof(const std::string proofKit, const std::string proof, const int valueToProof)
{
	std::string prf = proof;
	for(int i = 0; i < valueToProof; ++i) {
		prf = SHA256HashString(prf);
	}

	return !prf.compare(proofKit);
}

const std::string ProofKitPair::print()
{
	std::stringstream ss;

	ss << "Secret Key: " << this->secretKey << std::endl << "ProofKit: " << this->proofKit << std::endl;

	return ss.str();
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	ProofKitPair* proofKitPair;

	int choice;
	while(true) {
		std::cout << " 0 - Generate proof kit.\n";
		std::cout << " 1 - Make proof.\n";
		std::cout << " 2 - Check proof with proof kit.\n";
		std::cout << " Enter your choice and press return: ";

		std::cin >> choice;

		switch (choice)
		{
			case 0:
				std::cout << "Enter the current value to generate a proof kit from: ";
				int value;
				std::cin >> value;

				proofKitPair = new ProofKitPair(value);

				std::cout << proofKitPair->print();

				break;
			case 1:
				std::cout << "Story so far....\n";
				// rest of code here
				break;
			case 2:
				std::cout << "Ahahah, you really think I will help you?\n";
				// rest of code here
				break;
			default:
				std::cout << "Not a Valid Choice. \n";
				std::cout << "Choose again.\n";
				std::cin >> choice;
				break;
		}

	}

	delete proofKitPair;

	int toProveValue = std::atoi(argv[1]);

	//ProofKitPair proofKitPair(toProveValue);

	return 0;
}
