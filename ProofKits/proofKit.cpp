#include <iostream>
#include <cstdlib>
#include <sstream>
#include <memory>

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
	ProofKitPair();
	ProofKitPair(const int value);

	std::string getSecretKey() const { return this->secretKey; }
	std::string getProofKit() const { return this->proofKit; }
	int getValue() const { return this->value; }

	std::string makeProof(const int valueToProof) const;

	std::string print() const;

	bool isSet() const;

private:
	int value;
	std::string secretKey;
	std::string proofKit;
};

ProofKitPair::ProofKitPair()
{
	this->secretKey = "0";
	this->proofKit = "0";
}

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
	this->value = value;
}

std::string ProofKitPair::makeProof(const int valueToProof) const
{
	if(this->value < valueToProof) {
		throw std::invalid_argument("Value of the proofkit cannot be smaller than the value to proof!");
	}

	std::string proof = SHA256HashString(this->secretKey);

	for(int i = 0; i < (this->value - valueToProof); ++i) {
		proof = SHA256HashString(proof);
	}

	return proof;
}

bool checkProof(const std::string proofKit, const std::string proof, const int valueToProof)
{
	std::string prf = proof;
	for(int i = 0; i < valueToProof; ++i) {
		prf = SHA256HashString(prf);
	}

	return !prf.compare(proofKit);
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

int main(int argc, char* argv[])
{
	srand(time(NULL));

	std::unique_ptr<ProofKitPair> proofKitPair(new ProofKitPair());

	int value;
	std::string proof = "";

	int choice;
	while(true) {
		if(proofKitPair->isSet()) {
			std::cout << "ProofKit present:\n" << proofKitPair->print() << std::endl;
		}

		std::cout << " 0 - Generate proof kit.\n";
		std::cout << " 1 - Make proof.\n";
		std::cout << " 2 - Check proof with proof kit.\n";
		std::cout << " Enter your choice and press return: ";

		std::cin >> choice;

		switch (choice)
		{
			case 0:
				proof = "";
				std::cout << "Enter the current value to generate a proof kit from: ";
				std::cin >> value;

				proofKitPair.reset(new ProofKitPair(value));
				break;
			case 1:
				if(!proofKitPair->isSet()) {
					std::cout << "No proofkit generated yet!\n\n";
					break;
				}

				std::cout << "Enter the value you want to generate a proof for: ";
				std::cin >> value;

				proof = proofKitPair->makeProof(value);
				std::cout << "Proof: " << proof << "\n\n";

				break;
			case 2:
				if(!proof.compare("")) {
					std::cout << "No proof generated yet!\n\n";
					break;
				}

				std::cout << "The current proof is: " << proof << "\n\n";
				std::cout << "Enter the value to prove: ";
				std::cin >> value;

				bool correct = checkProof(proofKitPair->getProofKit(), proof, value);

				if(correct) {
					std::cout << "Proof is valid!\n\n";
					break;
				}

				std::cout << "Proof is not valid!\n\n";

				// rest of code here
				break;
			default:
				std::cout << "Not a Valid Choice. \n";
				std::cout << "Choose again.\n";
				std::cin >> choice;
				break;
		}

	}

	//ProofKitPair proofKitPair(toProveValue);

	return 0;
}
