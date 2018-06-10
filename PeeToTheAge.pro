QT += widgets network
requires(qtConfig(combobox))

INCLUDEPATH += ProofKits/include

HEADERS     = window.h ProofKits/include/HashHelper.h
SOURCES     = main.cpp \
              window.cpp \
              HelloHandler.cpp \
              ProofKits/src/ProofKit.cpp \
              ProofKits/src/SecretKey.cpp \
              ProofKits/src/ProofKitPair.cpp \
              ProofKits/src/RangeProof.cpp \
              ProofKits/src/Proof.cpp \
              ProofKits/src/Prover.cpp \

LIBS += -lpistache -lpthread -lcryptopp 

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/lineedits
INSTALLS += target
