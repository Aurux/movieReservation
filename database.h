#ifndef DATABASE_H
#define DATABASE_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>
#include <string>
#include <QSqlQueryModel>

class Database{
    public:
        void connectDB(bool dbExists);
        void createTables();
};


#endif // DATABASE_H
