using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Crypto
{
    abstract class Crypto
    {
        public abstract byte[] encrypt(byte[] buffer);
        public abstract byte[] decrypt(byte[] buffer);
    }
}
