#pragma once
#include "ICryptoAlgorithm.h"

// Crypto++
#include "aes.h"
#include "modes.h"
#include "filters.h"

class AESCryptoAlgorithm : public ICryptoAlgorithm
{
public:
	AESCryptoAlgorithm();
	Buffer encrypt(const Buffer& message, const Buffer& key) const override;
	Buffer decrypt(const Buffer& message, const Buffer& key) const override;
private:
	// Initialization vector
	CryptoPP::byte _iv[CryptoPP::AES::BLOCKSIZE];
};