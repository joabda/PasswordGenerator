#ifndef PMANAGER_H
#define PMANAGER_H

#include <sqlite3.h>
#include <QFile>
#include <cstring>
#include "rule.h"

using namespace std;

static QString defaultCreate = "CREATE TABLE Rules(name TEXT PRIMARY KEY, minChars UNSIGNED INTEGER, maxChars INTEGER, minCapital UNSIGNED INTEGER,"
                                                 " minNumbers INTEGER, specialChars UNSIGNED INTEGER);";

enum DbUse {Rules = 0, ExportMethods = 1};

template<typename T, typename C>  // T is QVector<Rule*> when DB is used for rules, or T is QVector<ExportMethod*> when used to get methods
class DataBase
{
public:
    DataBase(const DbUse& dbUse, const QString& dbName = "System")
    {
        dbName_ = dbName;
        container_ = new C();
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
    void setTableName(const QString& tableName);
    QString getTableName() const { return tableName_;}

    C getReadElements() const { return *container_;}

    void insertElement(const C* elementToInsert)
    {
        rc_ = sqlite3_open((dbName_.toStdString() + ".db").c_str(), &db_);

        if (rc_ != SQLITE_OK)
            error("Cannot open database");
        QString insert = "INSERT into " + tableName_ +
                         "(name, minChars, maxChars, minCapital,"
                         " minNumbers, specialChars) VALUES(";
        insert += "'" + elementToInsert->getName() + "'" + ", " + QString::number(elementToInsert->getMinChars()) + ", " + QString::number(elementToInsert->getMaxChars())
                + ", " + QString::number(elementToInsert->getMinCapital()) + ", " + QString::number(elementToInsert->getMinNumbers()) + ", "
                + QString::number(elementToInsert->getSpecialChars()) + ");";

        rc_ = sqlite3_exec(db_, insert.toStdString().c_str(), callback, nullptr, &errorMessage_);
        if (rc_ != SQLITE_OK )
           error("INSERT error");
    }
    void readElement()
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
            container_->push_back(new C(createRuleParameters[0], createRuleParameters[1].toUInt(), createRuleParameters[2].toInt(),
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

    int callbackRead(void* NotUsed, int argc, char** argv, char** azColName);

    ~DataBase();

private:
    sqlite3* db_;
    QString dbName_;
    QString tableName_;
    C container_;
    int rc_;
    char* errorMessage_;
    void error(const string& message);
};

#endif // PMANAGER_H
