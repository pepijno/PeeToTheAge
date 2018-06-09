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
	unsigned int value = std::atoi(argv[1]);

	RangeProof rangeProof(value);

	std::cout << "{"
		<< "\"lowerProofKit\": \"" << rangeProof.getLowerProofKit().getProofKit() << "\","
		<< "\"upperProofKit\": \"" << rangeProof.getUpperProofKit().getProofKit() << "\""
		<< "\"secret\": \"" << rangeProof.getSecretKey1().getKey() << "\""
		<< "}" << std::endl;

	return 0;
}
