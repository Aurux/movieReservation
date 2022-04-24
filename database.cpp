#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>
#include <string>
#include <QSqlQueryModel>
#include "database.h"
using namespace std;




void Database::connectDB(bool dbExists){
    if (dbExists){
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("movieDB");
        db.setUserName("root");
        db.setPassword("traffic-surprise-pungent");

        if(db.open()){
            qDebug() << "Connected to: " << db.databaseName();
        }
    }
    else {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");

        db.setUserName("root");
        db.setPassword("traffic-surprise-pungent");


        if (db.open()){
            qDebug() << "Connected to DB: " << db.hostName();
            QSqlQuery query;
            query.exec("CREATE DATABASE movieDB;");
            if(query.exec()) {
                query.exec("USE movieDB;");
            }
        }
        else qDebug() << "Failed to connect: " << db.lastError().text();
    }

}
void Database::createTables(){
    QSqlQuery query;
    query.exec("USE movieDB;");

    // Table creation
    if (query.exec("CREATE TABLE IF NOT EXISTS screens (screenID int NOT NULL AUTO_INCREMENT, totalSeats int, PRIMARY KEY (screenID));")){
        qDebug() << "Table screens created!";
        query.exec("TRUNCATE TABLE screens");
        query.exec("INSERT INTO screens (totalSeats) VALUES (100),(150),(192);");
        qDebug() << "Failed to insert screens: " << query.lastError().text();
    }
    else {

        qDebug() << "Table screens failed to create: " << query.lastError().text();

    }

    if (query.exec("CREATE TABLE IF NOT EXISTS movies (movieID int NOT NULL AUTO_INCREMENT, title VARCHAR(255), runtime VARCHAR(4), rating int(2), PRIMARY KEY (movieID));")){
        qDebug() << "Table movies created!";
        query.exec("TRUNCATE TABLE movies");
        query.exec("INSERT INTO movies (title, runtime, rating) VALUES ('The Batman', '2:56', 15),('Moonfall', '2:10', 12),('American Psycho', '1:42', 18),('Interstellar', '2:49', 12),('Hunt for the Wilderpeople', '1:40', 12);");
        qDebug() << "Failed to insert movies: " << query.lastError().text();
    }
    else {

        qDebug() << "Table movies failed to create: " << query.lastError().text();

    }

    if (query.exec("CREATE TABLE IF NOT EXISTS movieScreen (id int NOT NULL AUTO_INCREMENT, screenID int, title VARCHAR(255), showtime TIME, PRIMARY KEY (id));")){
        qDebug() << "Table movieScreen created!";
        query.exec("TRUNCATE TABLE movieScreen");
        query.exec("INSERT INTO movieScreen (screenID, title, showtime) VALUES (1, 'The Batman', '21:00:00'), (1, 'The Batman', '17:00:00'), (3, 'Hunt for the Wilderpeople', '11:30:00'), (2, 'American Psycho', '21:30:00'), (1, 'Interstellar', '12:30:00'), (2, 'Moonfall', '13:30:00');");
        qDebug() << "Failed to insert movieScreen: " << query.lastError().text();
    }
    else {

        qDebug() << "Table movieScreen failed to create: " << query.lastError().text();

    }
}


