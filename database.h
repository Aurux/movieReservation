#ifndef DATABASE_H
#define DATABASE_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>
#include <string>
#include <QSqlQueryModel>
#include <QByteArray>
#include <QDir>

class Database{
    public:
        bool connectDB(QString hostname, QString username, QString password);
        bool createTables();
        bool addExamples();
        bool deleteDB();
};


#endif // DATABASE_H
