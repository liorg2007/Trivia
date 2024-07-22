using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;
using System.IO;
using System.Windows.Input;

namespace Client.Crypto
{
    public struct KeyIvPair
    {
        public byte[] Key { get; set; }
        public byte[] IV { get; set; }
    }

    public class AES_Crypt
    {
        Aes aes;

        public AES_Crypt() 
        {
            aes = Aes.Create();
        }

        public byte[] Encrypt(string buffer)
        {
            byte[] encrypted;

            using (Aes aesAlg = Aes.Create())
            {
                aesAlg.Key = aes.Key;
                aesAlg.IV = aes.IV;

                // Create an encryptor to perform the stream transform.
                ICryptoTransform encryptor = aesAlg.CreateEncryptor(aesAlg.Key, aesAlg.IV);

                // Create the streams used for encryption.
                using (MemoryStream msEncrypt = new MemoryStream())
                {
                    using (CryptoStream csEncrypt = new CryptoStream(msEncrypt, encryptor, CryptoStreamMode.Write))
                    {
                        using (StreamWriter swEncrypt = new StreamWriter(csEncrypt))
                        {
                            //Write all data to the stream.
                            swEncrypt.Write(buffer);
                        }
                        encrypted = msEncrypt.ToArray();
                    }
                }
            }

            // Return the encrypted bytes from the memory stream.
            return encrypted;
        }

        public string Decrypt(byte[] buffer)
        {
            string decrypted;

            using (Aes aesAlg = Aes.Create())
            {
                aesAlg.Key = aes.Key;
                aesAlg.IV = aes.IV;

                // Create a decryptor to perform the stream transform.
                ICryptoTransform decryptor = aesAlg.CreateDecryptor(aesAlg.Key, aesAlg.IV);

                // Create the streams used for decryption.
                using (MemoryStream msDecrypt = new MemoryStream(buffer))
                {
                    using (CryptoStream csDecrypt = new CryptoStream(msDecrypt, decryptor, CryptoStreamMode.Read))
                    {
                        using (StreamReader srDecrypt = new StreamReader(csDecrypt))
                        {
                            decrypted = srDecrypt.ReadToEnd();
                        }
                    }
                }
            }

            return decrypted;
        }

        public KeyIvPair GetKeyIv()
        {
            KeyIvPair keyIvPair = new KeyIvPair();
            keyIvPair.Key = aes.Key;
            keyIvPair.IV = aes.IV;
            return keyIvPair;
        }
    }
}
