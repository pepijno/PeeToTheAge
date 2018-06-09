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
	std::string secretKey = argv[3];
	unsigned int value = std::atoi(argv[4]);
	unsigned int lower = std::atoi(argv[5]);
	unsigned int upper = std::atoi(argv[6]);

	RangeProof rangeProof(lowerProofKit, upperProofKit, secretKey, value);
	rangeProof.generateProof(lower, upper);

	std::cout << "{"
		<< "\"lowerProof\": \"" << rangeProof.getLowerProof().getProof() << "\","
		<< "\"upperProof\": \"" << rangeProof.getUpperProof().getProof() << "\""
		<< "}" << std::endl;

	return 0;
}
