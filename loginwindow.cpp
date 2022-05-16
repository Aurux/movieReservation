#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "staffwindow.h"
#include "database.h"
#include <QDir>

loginWindow::loginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::on_loginPushButton_clicked()
{
    QString staffIDtext;
    staffIDtext=ui->lineText_ID->text();

    QSqlQuery qry;
    qry.prepare(QString("SELECT * FROM staff WHERE staffid = :staffid"));
    qry.bindValue(":staffid", staffIDtext);

    if(!qry.exec()) {
        qDebug() << "Error getting staff id:\n" << qry.lastError();
    }else{

        while(qry.next()) {
            QString staffIDfromDB = qry.value(0).toString();

            if(staffIDfromDB == staffIDtext){
                staffWindow = new StaffWindow(this);
                staffWindow->show();
            }else{
                qDebug() << "failed to login:\n" << qry.lastError();
            }

        }

    }

}

