#include "JsonRequestPacketDeserializer.h"
#include <iostream>
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buff)
{
  int msgSize;
  LoginRequest request;
  json data;
  
  std::memcpy(&msgSize, &buff[CODE_FIELD_LENGTH], SIZE_FIELD_LENGTH);
  char* jsonString = new char[msgSize + 1];

  std::memcpy(jsonString, &buff[HEADER_FIELD_LENGTH], msgSize);
  jsonString[msgSize] = '\0'; 
  data = json::parse(jsonString);
  
  request.username = data["username"];
  request.password = data["password"];
   
  return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer buff)
{
    return SignupRequest();
}
