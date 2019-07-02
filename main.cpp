#include "mainwindow.h"
#include <QApplication>
#include <QVector>
#include <QDebug>
#include "login.h"
#include "rule.h"
#include "dataBase.h"
#include "rulesmanager.h"

#include "password.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Get Rules from DB on app start
    QString hello;
    DataBase<Rule*> rulesDB(Rules, hello);
    rulesDB.setTableName("Rules");
    rulesDB.readElement();
    QVector<Rule*> rules = rulesDB.getReadElements();
    RulesManager manager(rules);
    MethodManager methodManager;

    // Create login dialog and wait for successfull login before proceeding
    Login loginDialog;
    MainWindow mainWin(&manager, &methodManager);
    QObject::connect(&loginDialog, SIGNAL(successfullLogin()), &mainWin, SLOT(show()));
    loginDialog.exec();

    QVector<Rule*> defaultRules;
    defaultRules.push_back(new Rule("Hotmail", 8, 0, 1, 1, true));
    defaultRules.push_back(new Rule("Google", 8, 100, 0, 0, true));
    defaultRules.push_back(new Rule("Facebook", 8, 0, 1, 1, true));
    defaultRules.push_back(new Rule("Twitter", 10, 0, 1, 1, true));
    defaultRules.push_back(new Rule("Instagram", 6, 0, 1, 1, true));
    for (int i = 0;i < defaultRules.size();i++)
        rulesDB.insertElement(defaultRules[i]);

    // DEBUGGING
    qDebug() << rules.size() << endl;
    for (auto& i : rules)
        i->showRule();

    return a.exec();
}
