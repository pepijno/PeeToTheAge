#include <iostream>
#include <cstdlib>
#include <sstream>
#include <memory>

#include "HashHelper.h"
#include "ProofKitPair.h"
#include "Proof.h"

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

int main(int argc, char* argv[])
{
	srand(time(NULL));

	std::unique_ptr<ProofKitPair> proofKitPair(new ProofKitPair());
	std::unique_ptr<Proof> proof(new Proof());

	unsigned int value;

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
				proof.reset(new Proof());
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

				proof.reset(new Proof(*proofKitPair.get(), value));
				std::cout << proof->print();

				break;
			case 2:
				if(!proof->isSet()) {
					std::cout << "No proof generated yet!\n\n";
					break;
				}

				std::cout << proof->print();
				std::cout << "Enter the value to prove: ";
				std::cin >> value;

				if(proof->proveProof(*proofKitPair.get())) {
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
