#ifndef PMANAGER_H
#define PMANAGER_H

#include <sqlite3.h>
#include <QFile>
#include <cstring>
#include <QDebug>
#include "Rules/rule.h"
using namespace std;

class DataBase
{
public:
    DataBase(const QString& dbName = "System");

    void setDBName(const QString& dbName);
    QString getDBName() const;

    void setTableName(const QString& tableName);
    QString getTableName() const;

    QVector<Rule*> getReadElements() const;
    virtual void insertElement(Rule* elementToInsert);
    virtual void readElement();

    virtual ~DataBase();

private:
    int rc_;
    int numberOfColumns_;
    QVector<Rule*> container_;
    sqlite3* db_;
    QString dbName_;
    char* errorMessage_;
    void error(const string& message);
};
#endif // PMANAGER_H
