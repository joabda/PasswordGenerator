#ifndef PMANAGER_H
#define PMANAGER_H

#include <sqlite3.h>
#include <QFile>
#include <cstring>
#include <QDebug>
#include "Export/exportmethod.h"
#include "Rules/rule.h"
using namespace std;

template<typename T>  // T is Rule* when DB is used for rules, or T is ExportMethod* when used to get methods
class DataBase
{
public:
    DataBase(const QString& dbName = "System");

    void setDBName(const QString& dbName);
    QString getDBName() const;

    void setTableName(const QString& tableName);
    QString getTableName() const;

    QVector<T*> getReadElements() const;
    virtual void insertElement(T* elementToInsert);
    virtual void readElement();

    virtual ~DataBase();

protected:
    QString createQuery_;
    QString insertQuery_;
    int rc_;
    int numberOfColumns_;
    sqlite3_stmt* stmt_;
    QVector<T*> container_;

private:
    sqlite3* db_;
    QString dbName_;
    QString tableName_;
    char* errorMessage_;
    void error(const string& message);
};
#endif // PMANAGER_H
