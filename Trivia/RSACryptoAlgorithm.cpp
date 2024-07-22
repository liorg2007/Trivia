#include "RSACryptoAlgorithm.h"

RSACryptoAlgorithm::RSACryptoAlgorithm()
{
	_sk.GenerateRandomWithKeySize(_rng, k_keySize);
	_pk = CryptoPP::RSA::PublicKey(_sk);
}

Buffer RSACryptoAlgorithm::decrypt(const Buffer& message) const {
	CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(_sk);

	std::string decrypted;
	CryptoPP::ArraySource as(message.data(), message.size(), true,
		new CryptoPP::PK_DecryptorFilter(_rng, decryptor,
			new CryptoPP::StringSink(decrypted)
		)
	);

	return Buffer(decrypted.begin(), decrypted.end());
}

Buffer RSACryptoAlgorithm::getKey() const
{
	CryptoPP::ByteQueue queue;
	_pk.Save(queue);

	size_t size = queue.MaxRetrievable();
	std::vector<uint8_t> vec(size);

	queue.Get(vec.data(), vec.size());
	return vec;
}
