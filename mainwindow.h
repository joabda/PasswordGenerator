#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QMap>
#include <QDebug>
#include <QListWidget>
#include <QPair>
#include <QMap>
#include <QMessageBox>
#include "password.h"
#include "rulesmanager.h"
#include "Export/exportmethod.h"
#include "Export/pdf.h"
#include "Export/txt.h"
#include "Export/methodmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(RulesManager* rulesManager, MethodManager* methodManager, QWidget *parent = nullptr);
    void addRuleToView(Rule* toAdd);
    void addRulesToView(QMap<QString, Rule*> toAdd);
    void addMethodsToView(QMap<QString, ExportMethod*> toAdd);
    ~MainWindow();

public slots:
    void display();
    void selected(QListWidgetItem* checkedItem);
    void methodSelected(QListWidgetItem* checkedItem);

private slots:
    void on_selectedButton_clicked();

private:
    Ui::MainWindow *ui;
    MethodManager* methodManager_;
    RulesManager* rulesManager_;
    QVector<QPair<QString, QString>> namesOfSelectedRules_; // First element is the rule's name, second is the password
    QMap<QString, ExportMethod*> selectedMethods_;
    void design();
};

#endif // MAINWINDOW_H
