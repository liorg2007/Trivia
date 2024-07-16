#pragma once

#include "ICryptoAlgorithm.h"

#include <rsa.h>
#include <osrng.h>
#include <base64.h>
#include <hex.h>

class RSACryptoAlgorithm : public ICryptoAlgorithm
{
public:
	RSACryptoAlgorithm();

	//	for both there is no need for a key
	Buffer encrypt(const Buffer& message, const Buffer& key = {}) const override; 
	Buffer decrypt(const Buffer& message, const Buffer& key = {}) const override;

private:
	auto static constexpr k_keySize = 1024;

	CryptoPP::RSA::PrivateKey sk_;	//  secret/private key
	CryptoPP::RSA::PublicKey pk_;	//	public key
};