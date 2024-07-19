#pragma once

#include "Constants.h"

#include <rsa.h>
#include <osrng.h>
#include <base64.h>
#include <hex.h>

class RSACryptoAlgorithm
{
public:
	RSACryptoAlgorithm();

	Buffer decrypt(const Buffer& message) const;

private:
	auto static constexpr k_keySize = 1024;

	CryptoPP::RSA::PrivateKey _sk;	//  secret/private key
	CryptoPP::RSA::PublicKey _pk;	//	public key
	mutable CryptoPP::AutoSeededRandomPool _rng;	// rng number
};