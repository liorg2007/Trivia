using System;
using System.Collections.Generic;
using System.Formats.Asn1;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Client.Crypto
{
    public class RSA_Crypt
    {
        public static byte[] Encrypt(byte[] data, byte[] publicKey)
        {
            using (RSA rsa = RSA.Create())
            {
                rsa.ImportSubjectPublicKeyInfo(publicKey, out _);
                byte[] encryptedData = rsa.Encrypt(data, RSAEncryptionPadding.OaepSHA1);

                return encryptedData;
            }
        }
    }
}
