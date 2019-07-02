#include "pdf.h"

PDF::PDF() :
    ExportMethod ("PDF")
{
}

void PDF::saveAs(const QVector<QPair<QString, QString>>& password)
{

    QString html =
    "<div align=right>"
       "Montreal," + QDate::currentDate().toString() +
    "</div>"
    "<div align=left>"
       "Password Generator<br>"
       "https://github.com/joabda/PasswordGenerator<br>"
    "</div>"
    "<h1 align=center>Generated Passwords</h1>"
    "<p align=justify>";

    for (auto& element : password)
        html += "Generated password for " + element.first + " : " + element.second + "\n";

    html += "</p>"
    "<div align=right>sincerly</div>";

    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName("/tmp/test.pdf");
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    document.print(&printer);

//    QPdfWriter exportFile("Passwords");
//    exportFile.setPageSize(QPagedPaintDevice::A4);
//    exportFile.setPageMargins(QMargins(30, 30, 30, 30));

//    QPainter painter(&exportFile);
//    painter.setPen(Qt::black);
//    painter.setFont(QFont("Times", 10));

//    QRect rect = painter.viewport();

//    QString citydate = "Passwords generated " + QDate::currentDate().toString();

//    painter.drawText(rect, Qt::AlignRight, citydate);


//    QString sender = "Generator\n";
//    sender += "github.com/joabda/Generator\n";
//    sender += "Quebec, Canada\n";

//    painter.drawText(rect, Qt::AlignLeft, sender);
//    painter.end();
}

QString PDF::getName() const
{
    return name_;
}
