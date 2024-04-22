#include "Server.h"
#include "WSAInitializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"
#include "QuestionsRetriever.h"

#include "time.h"

int main()
{
	SqliteDatabase db(DATABASE_FILE_NAME);
	Sleep(1000);
	db.getQuestions(100);
	Sleep(1000);
	db.getQuestions(100);
	Sleep(1000);
	db.getQuestions(100);
	Sleep(1000);
	db.getQuestions(100);
	Sleep(1000);
	db.getQuestions(100);
	Sleep(1000);
	db.getQuestions(100);
	return 0;
}