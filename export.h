#ifndef EXPORT_H
#define EXPORT_H

#include <QDate>
#include <fstream>
#include <QVector>
#include <QPair>
#include <QPdfWriter>
#include <QPainter>

#include <QDebug>




#include <QTextDocument>
#include <QPrinter>
using namespace std;

class Export
{
public:
    Export();
    void PDF(const QVector<QPair<QString, QString>>& password) const;
    void TXT(const QVector<QPair<QString, QString>>& password) const;
    QVector<QString> getMethods() const;
    void saveAs(const QString& method, const QVector<QPair<QString, QString>>& passwords) const;
    ~Export() {}

private:
    QVector<QString> availableMethods_;
};

#endif // EXPORT_H
