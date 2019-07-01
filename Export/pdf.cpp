#include "pdf.h"

PDF::PDF()
{
    name_ = "PDF";
}

void PDF::saveAs(const QVector<QPair<QString, QString>>& password)
{
    QPdfWriter exportFile("Passwords");
    exportFile.setPageSize(QPagedPaintDevice::A4);
    exportFile.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&exportFile);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 10));

    QRect rect = painter.viewport();

    QString citydate = "Passwords generated " + QDate::currentDate().toString();

    painter.drawText(rect, Qt::AlignRight, citydate);


    QString sender = "Generator\n";
    sender += "github.com/joabda/Generator\n";
    sender += "Quebec, Canada\n";

    painter.drawText(rect, Qt::AlignLeft, sender);
    painter.end();
}

QString PDF::getName() const
{
    return name_;
}
