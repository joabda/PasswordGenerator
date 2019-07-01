#include "dataBase.h"

#include <QDebug>

DataBase::DataBase(const QString& dbName, const DbUse& dbUse)
/*
      @det 		Constructor of the Login class
      @param    QString     database's name
                QString     query to create the database (or table inside)
      @return 	void
*/
{
    dbName_ = dbName;
    readRules_ = new QVector<Rule*>();
    if(!QFile(dbName_ + ".db").exists())
    {
        rc_ = sqlite3_open((dbName_ + ".db").toStdString().c_str(), &db_);
        errorMessage_ = nullptr;

        if (rc_ != SQLITE_OK)
            error("Cannot open database");

        rc_ = sqlite3_exec(db_, createQuery.toStdString().c_str(), nullptr, nullptr, &errorMessage_);

        if (rc_ != SQLITE_OK )
           error("SQL error");
    }
}

// argc is the number of columns in the table
// argv are the values of the entries
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
   for(int i = 0; i < argc; i++)
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   printf("\n");
   return 0;
}

void DataBase::setTableName(const QString& tableName)
/*
      @det 		Setter for the table's name
      @param    QString     table's name
      @return 	void
*/
{
    tableName_ = tableName;
}

QString DataBase::getTableName() const
/*
      @det 		Getter for the table's name
      @param    void
      @return 	QString     table's name
*/
{
    return tableName_;
}

QVector<Rule*> DataBase::getReadElements() const
/*
      @det 		Getter of the rules read from the database
      @param    void
      @return 	QVector<Rules*>     vectors containing pointer to the rules that
                                        have been read from the database
*/
{
    return *readRules_;
}

void DataBase::error(const string& message)
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

void DataBase::insertElement(const Rule* toInsert)
/*
      @det 		Method to insert a rule in the database
      @param    Rules*      pointer to the rule that has to be inserted
      @return 	void
*/
{
    rc_ = sqlite3_open((dbName_.toStdString() + ".db").c_str(), &db_);

    if (rc_ != SQLITE_OK)
        error("Cannot open database");
    QString insert = "INSERT into " + tableName_ +
                     "(name, minChars, maxChars, minCapital,"
                     " minNumbers, specialChars) VALUES(";
    insert += "'" + toInsert->getName() + "'" + ", " + QString::number(toInsert->getMinChars()) + ", " + QString::number(toInsert->getMaxChars())
            + ", " + QString::number(toInsert->getMinCapital()) + ", " + QString::number(toInsert->getMinNumbers()) + ", "
            + QString::number(toInsert->getSpecialChars()) + ");";

    rc_ = sqlite3_exec(db_, insert.toStdString().c_str(), callback, nullptr, &errorMessage_);
    if (rc_ != SQLITE_OK )
       error("INSERT error");
}

void DataBase::readElement()
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
    sqlite3_stmt* stmt;
    rc_ = sqlite3_prepare_v2(db_, read.toStdString().c_str(), -1, &stmt, nullptr);

    if (rc_ != SQLITE_OK)
        error("Select Error");
    QString createRuleParameters[6];

    while( (rc_ = sqlite3_step(stmt) ) == SQLITE_ROW)
    {
        for (int i = 0; i < 6; i++)
            createRuleParameters[i] = QString::fromStdString(std::string(reinterpret_cast< char const* >(sqlite3_column_text(stmt, i))));
        readRules_->push_back(new Rule(createRuleParameters[0], createRuleParameters[1].toUInt(), createRuleParameters[2].toInt(),
                createRuleParameters[3].toUInt(),createRuleParameters[4].toUInt(), createRuleParameters[5]!="0"));
    }

    while(rc_ == SQLITE_ROW)
     {
         for(int i =  0; i < 6; i++)
            fprintf(stderr, "'%s' ", sqlite3_column_text(stmt, i));
         fprintf(stderr, "\n");
         rc_ = sqlite3_step(stmt);
     }
}

DataBase::~DataBase()
/*
      @det 		Destructor of the DataBase class will close the connection with the DataBase
      @param    void
      @return 	void
*/
{
    sqlite3_close(db_);
}
