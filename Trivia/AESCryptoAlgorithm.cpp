#include "AESCryptoAlgorithm.h"

// Key needs to be in length 16 (CryptoPP::AES::DEFAULT_KEYLENGTH)
Buffer AESCryptoAlgorithm::encrypt(const Buffer& message, const KeyAndIv& keyAndIv)
{
    Buffer encrypted;

    CryptoPP::AES::Encryption aesEncryption(keyAndIv.key.data(), keyAndIv.key.size());
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, keyAndIv.iv);

    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::VectorSink(encrypted));
    stfEncryptor.Put(message.data(), message.size());
    stfEncryptor.MessageEnd();

    return encrypted;
}

Buffer AESCryptoAlgorithm::decrypt(const Buffer& message, const KeyAndIv& keyAndIv)
{
    Buffer decrypted;

    CryptoPP::AES::Decryption aesDecryption(keyAndIv.key.data(), keyAndIv.key.size());
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, keyAndIv.iv);

    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::VectorSink(decrypted));
    stfDecryptor.Put(message.data(), message.size());
    stfDecryptor.MessageEnd();
    
    return decrypted;
}
