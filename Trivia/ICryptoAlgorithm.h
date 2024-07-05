#pragma once
#include "Constants.h"

class ICryptoAlgorithm
{
public:
	virtual Buffer encrypt(const Buffer& message) = 0;
	virtual Buffer decrypt(const Buffer& message) = 0;
};
