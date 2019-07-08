#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(RulesManager* rulesManager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    rulesManager_ = rulesManager;
    setWindowTitle("Generator");
    ui->setupUi(this);
    addRulesToView(rulesManager_->getCopyContainer());
    addMethodsToView(methodManager_.getMethods());
    QObject::connect(ui->rules, SIGNAL(itemChanged(QListWidgetItem*)),
                        this, SLOT(selected(QListWidgetItem*)));
    QObject::connect(ui->exportMethods, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(methodSelected(QListWidgetItem*)));
}

void MainWindow::selected(QListWidgetItem* checkedItem)
{
    if(checkedItem->checkState() == Qt::Checked)
        namesOfSelectedRules_.push_back(qMakePair<QString, QString>(checkedItem->text(), "Null"));
    else
        for(int index = 0; index < namesOfSelectedRules_.size(); index++)
            if(namesOfSelectedRules_[index].first == checkedItem->text())
                namesOfSelectedRules_.erase(namesOfSelectedRules_.begin() + index);
}

void MainWindow::methodSelected(QListWidgetItem* checkedMethod)
{
    if(checkedMethod->checkState() == Qt::Checked)
        selectedMethods_.push_back(checkedMethod->text());
    else
        for(int index = 0; index < selectedMethods_.size(); index++)
            if(selectedMethods_[index] == checkedMethod->text())
                selectedMethods_.erase(selectedMethods_.begin() + index);
}

void MainWindow::display()
{
    show();
}

void MainWindow::addRuleToView(Rule* toAdd)
{
    QListWidgetItem* itemToAdd = new QListWidgetItem(toAdd->getName(), ui->rules);
    itemToAdd->setFlags(itemToAdd->flags() | Qt::ItemIsUserCheckable);
    itemToAdd->setCheckState(Qt::Unchecked);
}

void MainWindow::addMethodsToView(QVector<QString> toAdd)
{
    for(auto& oneElement : toAdd)
    {
        QListWidgetItem* methodToAdd = new QListWidgetItem(oneElement, ui->exportMethods);
        methodToAdd->setFlags(methodToAdd->flags() | Qt::ItemIsUserCheckable);
        methodToAdd->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::addRulesToView(QMap<QString, Rule*> toAdd)
{
    for(auto& oneElement : toAdd)
        addRuleToView(oneElement);
}

void MainWindow::on_selectedButton_clicked()
{
    if(selectedMethods_.isEmpty())
    {
        QMessageBox mbox;
        mbox.setText("Please Select an export method.\n");
        mbox.exec();
    }
    else
    {
        Password generator;
        for(auto& element : namesOfSelectedRules_)
            element.second = generator(rulesManager_->findRule(element.first));
        for(auto& method : selectedMethods_)
            methodManager_.saveAs(method, namesOfSelectedRules_);

        QMessageBox mbox;
        mbox.setText("Passwords have been generated.\n");
        mbox.exec();
    }
}

void MainWindow::on_allButton_clicked()
{
    if(selectedMethods_.isEmpty())
    {
        QMessageBox mbox;
        mbox.setText("Please Select an export method.\n");
        mbox.exec();
    }
    else
    {
        for(int i = 0; i < ui->rules->count(); ++i)
            namesOfSelectedRules_.push_back(qMakePair<QString, QString>(ui->rules->item(i)->text(), "Null"));
        Password generator;
        for(auto& element : namesOfSelectedRules_)
            element.second = generator(rulesManager_->findRule(element.first));
        for(auto& method : selectedMethods_)
            methodManager_.saveAs(method, namesOfSelectedRules_);

        QMessageBox mbox;
        mbox.setText("Passwords have been generated.\n");
        mbox.exec();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
