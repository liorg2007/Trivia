using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Client.Requests;
using static Client.Helper;
using System.Text.Json;
using static Client.JsonPacketDeserializer;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace Client
{
    internal static class LoginSignup
    {
        public static byte[] CreateLoginRequest(LoginRequest loginRequest)
        {
            string json = JsonSerializer.Serialize(loginRequest);
            return Helper.createProtocol(json, (int)Codes.Login);
        }

        public static bool CheckLogin(ServerResponse response)
        {
            if (response.code == 1)
            {
                LoginResponse res = DeserializeLoginResponse(response.message);
                return res.status == 1;
            }

            throw new Exception("Problem with server");
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
            string json = JsonSerializer.Serialize(userData);
            return Helper.createProtocol(json, (int)Codes.Signup);
        }

        public static bool CheckSignup(ServerResponse response)
        {
            if (response.code == 2)
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
