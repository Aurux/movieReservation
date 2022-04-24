#include "database.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Database db;
    db.connectDB(false);
    db.createTables();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
