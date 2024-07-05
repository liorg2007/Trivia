#include "OTPCryptoAlgorithm.h"

Buffer OTPCryptoAlgorithm::encrypt(const Buffer& message, const Buffer& key) const
{
	Buffer encrypted;
	encrypted.reserve(message.size());
	int len = message.size();
	int keyLen = key.size();
	for (int i = 0; i < len; i++)
	{
		encrypted.push_back(message.at(i) ^ key.at(i % keyLen));
	}
	return encrypted;
}

Buffer OTPCryptoAlgorithm::decrypt(const Buffer& message, const Buffer& key) const
{
	return encrypt(message, key);
}
