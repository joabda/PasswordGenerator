#ifndef DBMETHODS_H
#define DBMETHODS_H

#include "dataBase.h"

class DBMethods : public DataBase<ExportMethod>
{
public:
    DBMethods();
    virtual void insertElement(ExportMethod* elementToInsert) override;
    virtual void readElement() override;
};

#endif // DBMETHODS_H
