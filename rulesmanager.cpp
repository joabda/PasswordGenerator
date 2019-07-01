#include "rulesmanager.h"

RulesManager::RulesManager(QVector<Rule*>& rules)
{
    for(auto& toAdd : rules)
        addRule(toAdd);
}

void RulesManager::addRule(Rule* toAdd)
{
    container_.insert(toAdd->getName(), new Rule(*toAdd));
}

QMap<QString, Rule*> RulesManager::getCopyContainer() const
{
    return container_;
}

Rule* RulesManager::findRule(const QString& ruleName) const
{
    auto found = container_.find(ruleName);
    if(found != container_.end())
        return found.value();
    return nullptr;
}

RulesManager::~RulesManager()
{
    for(auto& toDelete : container_)
        delete toDelete;
}
