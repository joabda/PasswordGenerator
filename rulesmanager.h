#ifndef RULESMANAGER_H
#define RULESMANAGER_H

#include <QVector>
#include <QMap>
#include "rule.h"

class RulesManager
{
public:
    RulesManager(QVector<Rule*>& rules);
    void addRule(Rule* toAdd);
    QMap<QString, Rule*> getCopyContainer() const;
    Rule* findRule(const QString& ruleName) const;
    ~RulesManager();

private:
    QMap<QString, Rule*> container_;
};

#endif // RULESMANAGER_H
