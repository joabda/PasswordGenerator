#include "dbmethods.h"

DBMethods::DBMethods() :
    DataBase()
{
    createQuery_ = "CREATE TABLE Methods(name TEXT PRIMARY KEY;";
    insertQuery_ = "INSERT into Methods (name) VALUES(";
    setTableName("Methods");
}
