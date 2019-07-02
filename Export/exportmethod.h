#ifndef EXPORTMETHOD_H
#define EXPORTMETHOD_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QDate>

class ExportMethod
{
public:
    ExportMethod(const QString& name) { name_ = name; }
    virtual void saveAs(const QVector<QPair<QString, QString>>& password);
    virtual QString getName() const;
    virtual ~ExportMethod() {}

protected:
    QString name_;
};

#endif // EXPORTMETHOD_H
