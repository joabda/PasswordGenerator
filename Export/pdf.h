#ifndef PDF_H
#define PDF_H

#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include "exportmethod.h"

class PDF : public ExportMethod
{
public:
    PDF();
    void saveAs(const QVector<QPair<QString, QString>>& password) override;
    QString getName() const override;
    ~PDF() override {}
};

#endif // PDF_H
