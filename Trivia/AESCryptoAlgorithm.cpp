#include "AESCryptoAlgorithm.h"

AESCryptoAlgorithm::AESCryptoAlgorithm()
{
    int16_t time = std::time(nullptr);
    std::memcpy(_iv, &time, CryptoPP::AES::BLOCKSIZE);
}

// Key needs to be in length 16 (CryptoPP::AES::DEFAULT_KEYLENGTH)
Buffer AESCryptoAlgorithm::encrypt(const Buffer& message, const Buffer& key) const
{
    Buffer encrypted;

    CryptoPP::AES::Encryption aesEncryption(key.data(), key.size());
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, _iv);

    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::VectorSink(encrypted));
    stfEncryptor.Put(message.data(), message.size());
    stfEncryptor.MessageEnd();

    return encrypted;
}

Buffer AESCryptoAlgorithm::decrypt(const Buffer& message, const Buffer& key) const
{
    Buffer decrypted;

    CryptoPP::AES::Decryption aesDecryption(key.data(), key.size());
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, _iv);

    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::VectorSink(decrypted));
    stfDecryptor.Put(message.data(), message.size());
    stfDecryptor.MessageEnd();
    
    return decrypted;
}
