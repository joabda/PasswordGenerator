#ifndef DBMETHODS_H
#define DBMETHODS_H

#include "dataBase.h"

class DBMethods : public DataBase<ExportMethod>
{
public:
    DBMethods();
    void insertElement(ExportMethod* elementToInsert) override;
    void readElement() override;
    ~DBMethods() override;
};

#endif // DBMETHODS_H
