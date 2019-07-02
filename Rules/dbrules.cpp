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
    DataBase::readElement();
    QString createRuleParameters[numberOfColumns_];

    while( (rc_ = sqlite3_step(stmt_) ) == SQLITE_ROW)
    {
        for (int i = 0; i < numberOfColumns_; i++)
            createRuleParameters[i] = QString::fromStdString(std::string(reinterpret_cast< char const* >(sqlite3_column_text(stmt_, i))));
        container_.push_back(new Rule(createRuleParameters[0], createRuleParameters[1].toUInt(), createRuleParameters[2].toInt(),
                createRuleParameters[3].toUInt(),createRuleParameters[4].toUInt(), createRuleParameters[5]!="0"));
    }

    while(rc_ == SQLITE_ROW)
     {
         for(int i =  0; i < numberOfColumns_; i++)
            fprintf(stderr, "'%s' ", sqlite3_column_text(stmt_, i));
         fprintf(stderr, "\n");
         rc_ = sqlite3_step(stmt_);
     }
}
