#include "dbrules.h"

DBRules::DBRules()
{
    createQuery_ = "CREATE TABLE Rules(name TEXT PRIMARY KEY, minChars UNSIGNED INTEGER, maxChars INTEGER, minCapital UNSIGNED INTEGER,"
                " minNumbers INTEGER, specialChars UNSIGNED INTEGER);";
    insertQuery_ = "INSERT into Rules (name, minChars, maxChars, minCapital,"
                " minNumbers, specialChars) VALUES(";
    setTableName("Rules");
}

void DBRules::insertElement(Rule* elementToInsert)
{
    insertQuery_ += "'" + elementToInsert->getName() + "'" + ", " + QString::number(elementToInsert->getMinChars()) + ", " + QString::number(elementToInsert->getMaxChars())
            + ", " + QString::number(elementToInsert->getMinCapital()) + ", " + QString::number(elementToInsert->getMinNumbers()) + ", "
            + QString::number(elementToInsert->getSpecialChars()) + ");";
    DataBase::insertElement(elementToInsert);
}

void DBRules::readElement()
{

}
