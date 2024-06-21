#include "IDatabase.h"
#include "SqliteDatabase.h"
#include "Constants.h"

std::shared_ptr<IDatabase> IDatabase::getInstance()
{
	// Here we choose what type of database the Server will use
	static std::shared_ptr<IDatabase> instance(new SqliteDatabase(DATABASE_FILE_NAME));
	return instance;
}
