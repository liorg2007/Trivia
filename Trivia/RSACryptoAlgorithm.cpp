#include "RSACryptoAlgorithm.h"

RSACryptoAlgorithm::RSACryptoAlgorithm()
{
	_sk.GenerateRandomWithKeySize(_rng, k_keySize);
	_pk = CryptoPP::RSA::PublicKey(_sk);
}

Buffer RSACryptoAlgorithm::decrypt(const Buffer& message) const
{
	std::vector<uint8_t> decryptedText;
	CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(_sk);

	// Create a StringSource with the ciphertext vector
	std::string decrypted;
	CryptoPP::ArraySource as(message.data(), message.size(), true,
		new CryptoPP::PK_DecryptorFilter(_rng, decryptor,
			new CryptoPP::StringSink(decrypted)
		)
	);

	// Convert the decrypted text back to std::vector<uint8_t>
	decryptedText.assign(decrypted.begin(), decrypted.end());

	return decryptedText;
}
