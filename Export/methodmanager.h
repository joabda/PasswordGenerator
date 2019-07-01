#ifndef METHODMANAGER_H
#define METHODMANAGER_H

#include <QMap>
#include <QString>
#include <QListWidgetItem>
#include "Export/exportmethod.h"
#include "Export/pdf.h"
#include "Export/txt.h"

class MethodManager
{
public:
    MethodManager();

    ExportMethod* findType(const QString& name) const;

    void addMethod(ExportMethod* toAdd);

    void removeMethod(QListWidgetItem* checkedMethod);

    QMap<QString, ExportMethod*> getMethods() const;

    ~MethodManager() {}

private:
    QMap<QString, ExportMethod*> availableMethods_;
};

#endif // METHODMANAGER_H
