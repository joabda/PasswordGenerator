#include "dataBase.h"

template<typename T>
DataBase<T>::DataBase(const QString& dbName)
/*
      @det 		Constructor of the Login class
      @param    QString     database's name
                QString     query to create the database (or table inside)
      @return 	void
*/
{
    dbName_ = dbName;
    if(!QFile(dbName_ + ".db").exists())
    {
        rc_ = sqlite3_open((dbName_ + ".db").toStdString().c_str(), &db_);
        errorMessage_ = nullptr;

        if (rc_ != SQLITE_OK)
            error("Cannot open database");

        rc_ = sqlite3_exec(db_, createQuery_.toStdString().c_str(), nullptr, nullptr, &errorMessage_);

        if (rc_ != SQLITE_OK )
           error("SQL error");
    }
}

template<typename T>
void DataBase<T>::setDBName(const QString& dbName)
{
    dbName_ = dbName;
}

template<typename T>
QString DataBase<T>::getDBName() const
{
    return dbName_;
}

template<typename T>
void DataBase<T>::setTableName(const QString& tableName)
{
    tableName_ = tableName;
}

template<typename T>
QString DataBase<T>::getTableName() const
{
    return tableName_;
}

// argc is the number of columns in the table
// argv are the values of the entries
static int callback(void* unUsed, int count, char** data, char** azColName)
{
   for(int i = 0; i < count; i++)
      printf("%s = %s\n", azColName[i], data[i] ? data[i] : "NULL");
   printf("\n");
   return 0;
}

template<typename T>
QVector<T*> DataBase<T>::getReadElements() const
/*
      @det 		Getter of the rules read from the database
      @param    void
      @return 	QVector<Rules*>     vectors containing pointer to the rules that
                                        have been read from the database
*/
{
    return container_;
}

template<typename T>
void DataBase<T>::error(const string& message)
/*
      @det 		Method to print database's error and free the error message
      @param    string      customized message to get along with the database's message
      @return 	void
*/
{
    fprintf(stderr, "%s: %s\n", message.c_str(), sqlite3_errmsg(db_));
    sqlite3_free(errorMessage_);
    sqlite3_close(db_);
}

template<typename T>
void DataBase<T>::insertElement(T* toInsert)
/*
      @det 		Method to insert a rule in the database
      @param    Rules*      pointer to the rule that has to be inserted
      @return 	void
*/
{
    rc_ = sqlite3_open((dbName_.toStdString() + ".db").c_str(), &db_);

    if (rc_ != SQLITE_OK)
        error("Cannot open database");

    rc_ = sqlite3_exec(db_, insertQuery_.toStdString().c_str(), callback, nullptr, &errorMessage_);
    if (rc_ != SQLITE_OK )
       error("INSERT error");
}

template<typename T>
void DataBase<T>::readElement()
/*
      @det 		Method to read all the rulse from the database
                    and save them into the container
      @param    void
      @return 	void
*/
{
    rc_ = sqlite3_open((dbName_.toStdString() + ".db").c_str(), &db_);

    if (rc_ != SQLITE_OK)
        error("Cannot open database");

    QString read = "SELECT * from " + tableName_;

    rc_ = sqlite3_prepare_v2(db_, read.toStdString().c_str(), -1, &stmt_, nullptr);

    if (rc_ != SQLITE_OK)
        error("Select Error");
    else
        numberOfColumns_ = sqlite3_data_count(stmt_);
}

template<typename T>
DataBase<T>::~DataBase()
/*
      @det 		Destructor of the DataBase class will close the connection with the DataBase
      @param    void
      @return 	void
*/
{
    sqlite3_close(db_);
}

template class DataBase<Rule>;
template class DataBase<ExportMethod>;
