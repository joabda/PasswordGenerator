#ifndef PDF_H
#define PDF_H

#include <QPdfWriter>
#include <QPainter>
#include "exportmethod.h"

class PDF : public ExportMethod
{
public:
    PDF();
    void saveAs(const QVector<QPair<QString, QString>>& password) override;
    QString getName() const override;
    ~PDF() {}
};

#endif // PDF_H
