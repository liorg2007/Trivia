using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Crypto
{
    public abstract class Crypto
    {
        public abstract byte[] encrypt(string buffer);
        public abstract string decrypt(byte[] buffer);
    }
}
