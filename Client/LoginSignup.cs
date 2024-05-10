using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Client.Requests;
using System.Text.Json;
using static Client.JsonPacketDeserializer;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace Client
{
    internal static class LoginSignup
    {
        public static bool SendLoginRequest(Server server, string username, string password)
        {
            var reqStruct = new LoginRequest { username=username, password=password };
            ServerResponse res = Helper.SendRequest(server, Code.Login, JsonSerializer.SerializeToUtf8Bytes(reqStruct));
            LoginResponse deserializedRes = DeserializeLoginResponse(res.message);
            return deserializedRes.status == 1; // Successful login
        }

        public static bool CheckSignupInput(SignupRequest input)
        {
            bool passwordMatch = Regex.IsMatch(input.password, PASSWORD_REGEX);
            bool emailMatch = Regex.IsMatch(input.email, EMAIL_REGEX);
            bool addressMatch = Regex.IsMatch(input.address, ADDRESS_REGEX);
            bool phoneNumberMatch = Regex.IsMatch(input.phoneNumber, PHONE_NUMBER_REGEX);
            bool birthDateMatch = Regex.IsMatch(input.birthDate, BIRTH_DATE_REGEX);
            return passwordMatch && emailMatch && addressMatch && phoneNumberMatch && birthDateMatch;
        }

        public static byte[] CreateSignupRequest(SignupRequest userData)
        {
            var json = JsonSerializer.SerializeToUtf8Bytes(userData);
            return Helper.createProtocol(Code.Signup, json);
        }

        public static bool CheckSignup(ServerResponse response)
        {
            if (response.code == Code.Signup)
            {
                SignupResponse res = DeserializeSignupResponse(response.message);
                return res.status == 1;
            }

            throw new Exception("Problem with server");
        }

        public const string PASSWORD_REGEX = "^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$";
        public const string EMAIL_REGEX = "^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$";
        public const string ADDRESS_REGEX = "^[a-zA-Z]+,[\\d]+,[a-zA-Z]+$";
        public const string PHONE_NUMBER_REGEX = "^0[0-9]{9}$";
        public const string BIRTH_DATE_REGEX = "^(0?[1-9]|[12][0-9]|3[01])[\\/\\-](0?[1-9]|1[012])[\\/\\-]\\d{4}$";
    }
}
