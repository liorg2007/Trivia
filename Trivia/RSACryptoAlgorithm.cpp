#include "RSACryptoAlgorithm.h"

RSACryptoAlgorithm::RSACryptoAlgorithm()
{
	CryptoPP::AutoSeededRandomPool rng;
	sk_.GenerateRandomWithKeySize(rng, k_keySize);
	pk_ = CryptoPP::RSA::PublicKey(sk_);
}
