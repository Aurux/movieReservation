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
    }
    else {
        ui->statusLabel->setText("Database connection failed.");
        ui->statusLabel->adjustSize();
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


void DBSetupWindow::on_buttonBox_accepted()
{
    MainWindow *w = new MainWindow;
    w->show();
}


void DBSetupWindow::on_buttonBox_rejected()
{
    QApplication::quit();
}

