#include "dbsetupwindow.h"
#include "mainwindow.h"
#include "ui_dbsetupwindow.h"
#include "database.h"
DBSetupWindow::DBSetupWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBSetupWindow)
{
    ui->setupUi(this);
    setWindowTitle("Movie Reservation - Connect to Database");

}

DBSetupWindow::~DBSetupWindow()
{
    delete ui;
}
Database db;
void DBSetupWindow::on_testConnBtn_clicked()
{
    QString hostname = ui->hostInput->text();
    QString username = ui->userInput->text();
    QString password = ui->passInput->text();

    bool connectSuccess = db.connectDB(hostname,username,password);
    if (connectSuccess){
        ui->statusLabel->setText("Database connection successful!");
        ui->statusLabel->adjustSize();
        ui->createDBBtn->setEnabled(true);
        ui->exampleDataBtn->setEnabled(true);
        ui->clearDBBtn->setEnabled(true);
        ui->buttonBox->setEnabled(true);
    }
    else {
        ui->statusLabel->setText("Database connection failed.");
        ui->statusLabel->adjustSize();
        ui->createDBBtn->setEnabled(false);
        ui->exampleDataBtn->setEnabled(false);
    }
}


void DBSetupWindow::on_createDBBtn_clicked()
{
    ui->statusLabel->setText("Creating tables...");
    ui->statusLabel->adjustSize();
    bool createSuccess = db.createTables();


    if (createSuccess){
        ui->statusLabel->setText("Table creation successful!");
        ui->statusLabel->adjustSize();
    }
    else {
        ui->statusLabel->setText("Table creation failed.");
        ui->statusLabel->adjustSize();
    }
}

void DBSetupWindow::on_exampleDataBtn_clicked()
{
    bool exampleSuccess = db.addExamples();

    if (exampleSuccess){
        ui->statusLabel->setText("Example data successfully added!");
        ui->statusLabel->adjustSize();
    }
    else {
        ui->statusLabel->setText("Failed to add example data.");
        ui->statusLabel->adjustSize();
    }
}


void DBSetupWindow::on_buttonBox_accepted()
{
    on_testConnBtn_clicked();
    MainWindow *w = new MainWindow;
    w->show();
}



void DBSetupWindow::on_buttonBox_2_clicked(QAbstractButton *button)
{
    ui->hostInput->clear();
    ui->userInput->clear();
    ui->passInput->clear();
    ui->testConnBtn->setEnabled(false);
    ui->createDBBtn->setEnabled(false);
    ui->exampleDataBtn->setEnabled(false);
    ui->clearDBBtn->setEnabled(false);
    ui->buttonBox->setEnabled(false);
    ui->statusLabel->setText("");
}


void DBSetupWindow::on_passInput_textChanged(const QString &arg1)
{
    ui->testConnBtn->setEnabled(true);
}


void DBSetupWindow::on_userInput_textChanged(const QString &arg1)
{
    ui->testConnBtn->setEnabled(true);
}


void DBSetupWindow::on_hostInput_textChanged(const QString &arg1)
{
    ui->testConnBtn->setEnabled(true);
}





void DBSetupWindow::on_clearDBBtn_clicked()
{
    bool success = db.deleteDB();

    if (success){
        ui->statusLabel->setText("Database deleted successfully.");
        ui->createDBBtn->setEnabled(false);
        ui->exampleDataBtn->setEnabled(false);
        ui->clearDBBtn->setEnabled(false);
        ui->buttonBox->setEnabled(false);
    }
    else {
        ui->statusLabel->setText("Failed to delete database.");
    }
}

