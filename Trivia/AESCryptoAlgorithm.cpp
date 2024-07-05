#include "AESCryptoAlgorithm.h"

AESCryptoAlgorithm::AESCryptoAlgorithm()
{
    int16_t time = std::time(nullptr);
    std::memcpy(_iv, &time, CryptoPP::AES::BLOCKSIZE);
}

Buffer AESCryptoAlgorithm::encrypt(const Buffer& message, const Buffer& key) const
{
    Buffer encrypted;

    CryptoPP::AES::Encryption aesEncryption(key.data(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, _iv);

    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::VectorSink(encrypted));
    stfEncryptor.Put(message.data(), message.size());
    stfEncryptor.MessageEnd();

    return encrypted;
}

Buffer AESCryptoAlgorithm::decrypt(const Buffer& message, const Buffer& key) const
{
    return Buffer();
}
