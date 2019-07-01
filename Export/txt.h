#ifndef TXT_H
#define TXT_H

#include <fstream>
#include "exportmethod.h"

using namespace std;

class TXT : public ExportMethod
{
public:
    TXT();
    void saveAs(const QVector<QPair<QString, QString>>& password) override;
    QString getName() const override;
    ~TXT() {}
};

#endif // TXT_H
