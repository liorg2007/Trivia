#include "Server.h"
#include "WSAInitializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"
#include "QuestionsRetriever.h"

int main()
{
	SqliteDatabase db(DATABASE_FILE_NAME);
	db.insertNewQuestions(10);
	return 0;
}