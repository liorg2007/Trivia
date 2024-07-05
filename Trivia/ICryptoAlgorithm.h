#pragma once
#include "Constants.h"

class ICryptoAlgorithm
{
public:
	virtual Buffer encrypt(const Buffer& message, const Buffer& key) const = 0;
	virtual Buffer decrypt(const Buffer& message, const Buffer& key) const = 0;
};
