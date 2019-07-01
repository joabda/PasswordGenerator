#ifndef EXPORTMETHOD_H
#define EXPORTMETHOD_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QDate>

class ExportMethod
{
public:
    virtual void saveAs(const QVector<QPair<QString, QString>>& password) = 0;
    virtual QString getName() const = 0;
    virtual ~ExportMethod() {}

protected:
    QString name_;
};

#endif // EXPORTMETHOD_H
