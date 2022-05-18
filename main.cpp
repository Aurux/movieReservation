#include "database.h"
#include "dbsetupwindow.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //Database db;
    //db.connectDB("localhost","root","traffic-surprise-pungent");
    //db.createTables();

    QApplication a(argc, argv);



    DBSetupWindow *DBSetupWindow = new class DBSetupWindow;
    DBSetupWindow->setModal(true);
    DBSetupWindow->exec();
    return a.exec();
}
