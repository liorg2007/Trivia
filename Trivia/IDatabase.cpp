#include "IDatabase.h"
#include "SqliteDatabase.h"
#include "Constants.h"

IDatabase* IDatabase::getInstance()
{
	// Here we choose what type of database the Server will use
	static IDatabase* instance = new SqliteDatabase(DATABASE_FILE_NAME);
	return instance;
}
