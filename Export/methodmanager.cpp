#include "methodmanager.h"

MethodManager::MethodManager()
{

}

ExportMethod* MethodManager::findType(const QString& name) const
{
    if(name == "PDF")
        return new PDF();
    else if(name == "Text")
        return new TXT();
}

void MethodManager::addMethod(ExportMethod* toAdd)
{
    availableMethods_.insert(toAdd->getName(), toAdd);
}

void MethodManager::removeMethod(QListWidgetItem* checkedMethod)
{
//    for(int index = 0; index < availableMethods_.size(); index++)
//        if(availableMethods_[index] == checkedMethod->text())
//            availableMethods_.erase(availableMethods_.begin() + index);
}

QMap<QString, ExportMethod*> MethodManager::getMethods() const
{
    return availableMethods_;
}
