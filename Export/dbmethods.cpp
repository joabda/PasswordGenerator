#include "dbmethods.h"

DBMethods::DBMethods() :
    DataBase()
{
    createQuery_ = "CREATE TABLE Methods(name TEXT PRIMARY KEY;";
    insertQuery_ = "INSERT into Methods (name) VALUES(";
    setTableName("Methods");
}

void DBMethods::readElement()
{
    DataBase::readElement();
    QString createMethodParameter;

    while( (rc_ = sqlite3_step(stmt_) ) == SQLITE_ROW)
    {
        createMethodParameter = QString::fromStdString(std::string(reinterpret_cast< char const* >(sqlite3_column_text(stmt_, 0))));
        container_.push_back(new ExportMethod(createMethodParameter));
    }

    while(rc_ == SQLITE_ROW)
     {
         for(int i =  0; i < numberOfColumns_; i++)
            fprintf(stderr, "'%s' ", sqlite3_column_text(stmt_, i));
         fprintf(stderr, "\n");
         rc_ = sqlite3_step(stmt_);
     }
}
