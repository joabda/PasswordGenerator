#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QMap>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include "password.h"
#include "export.h"
#include "Rules/rulesmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(RulesManager* rulesManager, QWidget *parent = nullptr);
    void addRuleToView(Rule* toAdd);
    void addRulesToView(QMap<QString, Rule*> toAdd);
    void addMethodsToView(QVector<QString> toAdd);
    ~MainWindow();

public slots:
    void display();
    void selected(QListWidgetItem* checkedItem);
    void methodSelected(QListWidgetItem* checkedItem);

private slots:
    void on_selectedButton_clicked();

private:
    Ui::MainWindow *ui;
    RulesManager* rulesManager_;
    Export methodManager_;
    QVector<QPair<QString, QString>> namesOfSelectedRules_; // First element is the rule's name, second is the password
    QVector<QString> selectedMethods_;
    void design();
};

#endif // MAINWINDOW_H
