#include <iostream>
#include <cstdlib>
#include <sstream>
#include <memory>

#include "HashHelper.h"
#include "ProofKitPair.h"
#include "Proof.h"
#include "RangeProof.h"
#include "Prover.h"

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
	std::string lowerProofKit = argv[1];
	std::string upperProofKit = argv[2];
	std::string secretKey = argv[3];
	unsigned int value = std::atoi(argv[4]);
	unsigned int lower = std::atoi(argv[5]);
	unsigned int upper = std::atoi(argv[6]);
	/*srand(time(NULL));

	std::unique_ptr<RangeProof> rangeProof(new RangeProof());

	unsigned int value;
	unsigned int second;

	int choice;
	while(true) {
		std::cout << " 0 - Generate proof kit.\n";
		std::cout << " 1 - Make proof.\n";
		std::cout << " 2 - Check proof with proof kit.\n";
		std::cout << " Enter your choice and press return: ";

		std::cin >> choice;

		if(choice == 0) {
			std::cout << "Enter the current value to generate a proof kit from: ";
			std::cin >> value;

			rangeProof.reset(new RangeProof(value));
		} else if(choice == 1) {
			std::cout << "Enter the lower bound you want generate a proof for: ";
			std::cin >> value;
			std::cout << "Enter the upper bound you want to generate a proof for: ";
			std::cin >> second;

			rangeProof->generateProof(value, second);
		} else if(choice == 2) {
			std::cout << "Enter the lower bound to prove: ";
			std::cin >> value;
			std::cout << "Enter the upper bound to prove: ";
			std::cin >> second;

			Prover prover(rangeProof->getLowerProofKit(), rangeProof->getUpperProofKit(), rangeProof->getLowerProof(), rangeProof->getUpperProof());

			if(prover.prove(value, second)) {
				std::cout << "Proof is valid!\n\n";
			} else {
				std::cout << "Proof is not valid!\n\n";
			}
		} else {
			std::cout << "Not a Valid Choice. \n";
			std::cout << "Choose again.\n";
			std::cin >> choice;
		}

	}*/

	RangeProof rangeProof(lowerProofKit, upperProofKit, secretKey, value);
	rangeProof.generateProof(lower, upper);

	std::cout << "{"
		<< "\"lowerProof\": \"" << rangeProof.getLowerProof().getProof() << "\","
		<< "\"upperProof\": \"" << rangeProof.getUpperProof().getProof() << "\""
		<< "}" << std::endl;

	return 0;
}
