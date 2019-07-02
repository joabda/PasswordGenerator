#ifndef DBRULES_H
#define DBRULES_H
#include "dataBase.h"

class DBRules : public DataBase<Rule>
{
public:
    DBRules();
    void insertElement(Rule* elementToInsert) override;
    void readElement() override;
};

#endif // DBRULES_H
