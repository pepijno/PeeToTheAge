#CC=g++
#CPPFLAGS=-std=c++1y -O2 -fpermissive -lcryptopp
#MAIN=main.o
#EXECUTABLE=bin/proofKit
#INCLDIR=include/
#CPP_FILES := $(wildcard src/*.cpp)
#OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
#
#DEPDIR := .d
#$(shell mkdir -p $(DEPDIR) >/dev/null)
#DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
#
#COMPILE.cc = $(CC) $(DEPFLAGS) $(CPPFLAGS) -I$(INCLDIR) -c
#POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d
#
#all: $(EXECUTABLE)
#
#$(EXECUTABLE): obj/$(MAIN) $(OBJ_FILES)
#	$(CC) $(CPPFLAGS) -o $@ $^
#
#obj/%.o : src/%.cpp $(DEPDIR)/%.d
#	$(COMPILE.cc) $(OUTPUT_OPTION) $<
#	$(POSTCOMPILE)
#
#clean:
#	rm -f $(OBJ_FILES) $(MAIN) $(EXECUTABLE)
#	rm -rf $(DEPDIR)
#
#$(DEPDIR)/%.d: ;
#.PRECIOUS: $(DEPDIR)/%.d
#
#-include $(addprefix .d/,$(notdir $(CPP_FILES:.cpp=.d)))

all:
	g++ -o bin/generateProof src/generateProof.cpp src/Proof.cpp src/ProofKit.cpp src/ProofKitPair.cpp src/Prover.cpp src/RangeProof.cpp src/SecretKey.cpp -Iinclude -Wall -fpermissive -lcryptopp -D_DEBUG
	g++ -o bin/makeProofKit src/makeProofKit.cpp src/Proof.cpp src/ProofKit.cpp src/ProofKitPair.cpp src/Prover.cpp src/RangeProof.cpp src/SecretKey.cpp -Iinclude -Wall -fpermissive -lcryptopp -D_DEBUG
	g++ -o bin/checkProof src/checkProof.cpp src/Proof.cpp src/ProofKit.cpp src/ProofKitPair.cpp src/Prover.cpp src/RangeProof.cpp src/SecretKey.cpp -Iinclude -Wall -fpermissive -lcryptopp -D_DEBUG
