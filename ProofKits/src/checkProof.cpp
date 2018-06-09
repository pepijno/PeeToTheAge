#include <iostream>
#include <cstdlib>
#include <sstream>
#include <memory>

#include "HashHelper.h"
#include "ProofKitPair.h"
#include "Proof.h"
#include "RangeProof.h"
#include "Prover.h"

int main(int argc, char* argv[])
{
	std::string lowerProofKit = argv[1];
	std::string upperProofKit = argv[2];
	std::string lowerProof = argv[3];
	std::string upperProof = argv[4];
	unsigned int lower = std::atoi(argv[5]);
	unsigned int upper = std::atoi(argv[6]);

	ProofKit lProofKit(1, lowerProofKit);
	ProofKit uProofKit(1, upperProofKit);
	Proof lProof(lowerProof);
	Proof uProof(upperProof);
	Prover prover(lProofKit, uProofKit, lProof, uProof);

	bool proven = prover.prove(lower, upper);

	if(proven) {
		std::cout << "\n\n\n\nThe proof has been VERIFIED!!\n\n\n";
	} else {
		std::cout << "\n\n\n\nThe proof has NOT been VERIFIED!!\n\n\n";
	}

	return 0;
}
