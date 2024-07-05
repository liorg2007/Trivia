#pragma once
#include "ICryptoAlgorithm.h"
class OTPCryptoAlgorithm : public ICryptoAlgorithm
{
public:
	Buffer encrypt(const Buffer& message, const Buffer& key) const override;
	Buffer decrypt(const Buffer& message, const Buffer& key) const override;
};

