#pragma once
#include "ICryptoAlgorithm.h"

// Crypto++
#include <aes.h>
#include <modes.h>
#include <filters.h>

struct KeyAndIv {
	Buffer key;
	CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
};


static class AESCryptoAlgorithm
{
public:
	static Buffer encrypt(const Buffer& message, const KeyAndIv& keyAndIv);
	static Buffer decrypt(const Buffer& message, const KeyAndIv& keyAndIv);
};