#include "database.h"




bool Database::connectDB(QString hostname, QString username, QString password){

        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(hostname);

        db.setUserName(username);
        db.setPassword(password);


        if (db.open()){
            qDebug() << "Connected to DB: " << db.hostName();
            QSqlQuery query;
            query.exec("USE movieDB;");
            return true;


        }
        else {
            qDebug() << "Failed to connect: " << db.lastError().text();
            return false;
        }


}
bool Database::createTables(){
    bool success = true;
    QSqlQuery query;

    query.exec("CREATE DATABASE movieDB;");

    query.exec("USE movieDB;");

    // Table creation
    if (query.exec("CREATE TABLE IF NOT EXISTS screens (screenID int NOT NULL AUTO_INCREMENT, totalSeats int, PRIMARY KEY (screenID));")){
        qDebug() << "Table screens created!";
        if(!query.exec("TRUNCATE TABLE screens;")){
                qDebug() << "Failed to truncate screens: " << query.lastError().text();
        }
        if(!query.exec("INSERT INTO screens (totalSeats) VALUES (208),(160),(80);")){
             qDebug() << "Failed to insert screens: " << query.lastError().text();
        }
        query.exec("DELETE FROM screens WHERE screenID > 3;");
        qDebug() << "Screen delete: " << query.lastError().text();
    }
    else {

        qDebug() << "Table screens failed to create: " << query.lastError().text();
        success = false;

    }

    if (query.exec("CREATE TABLE IF NOT EXISTS movies (movieID int NOT NULL AUTO_INCREMENT, title VARCHAR(255), runtime VARCHAR(4), rating VARCHAR(3), poster VARCHAR(255), PRIMARY KEY (movieID));")){
        qDebug() << "Table movies created!";
        query.exec("TRUNCATE TABLE movies");
        query.prepare("INSERT INTO movies (title, runtime, rating, poster) VALUES ('The Batman', '2:56', 15, :poster),('Moonfall', '2:10', 12, :poster2),('American Psycho', '1:42', 18, :poster3),('Interstellar', '2:49', 12, :poster4),('Hunt for the Wilderpeople', '1:40', 12, :poster5);");
        qDebug() << "Failed to insert movies: " << query.lastError().text();
           query.bindValue( ":poster", ":/new/icon/images/batman.png");
           query.bindValue( ":poster2", ":/new/icon/images/moonfall.png");
           query.bindValue( ":poster3", ":/new/icon/images/psycho.png");
           query.bindValue( ":poster4", ":/new/icon/images/interstellar.png");
           query.bindValue( ":poster5", ":/new/icon/images/hftwp.png");
           if( !query.exec() )
               qDebug() << "Error inserting image into table:\n" << query.lastError();
    }
    else {

        qDebug() << "Table movies failed to create: " << query.lastError().text();
        success = false;

    }

    if (query.exec("CREATE TABLE IF NOT EXISTS showtimes (id int NOT NULL AUTO_INCREMENT, screenID int, title VARCHAR(255), showtime TIME, FOREIGN KEY(screenID) REFERENCES screens(screenID), PRIMARY KEY (id));")){
        qDebug() << "Table movieScreen created!";
        query.exec("TRUNCATE TABLE showtimes");
        query.exec("INSERT INTO showtimes (screenID, title, showtime) VALUES (1, 'The Batman', '21:00:00'), (1, 'The Batman', '17:00:00'), (3, 'Hunt for the Wilderpeople', '11:30:00'), (2, 'American Psycho', '21:30:00'), (1, 'Interstellar', '12:30:00'), (2, 'Moonfall', '13:30:00');");
        qDebug() << "Failed to insert showtimes: " << query.lastError().text();
        query.exec("DELETE FROM showtimes WHERE id > 6;");
    }
    else {

        qDebug() << "Table movieScreen failed to create: " << query.lastError().text();
        success = false;

    }

    if (query.exec("CREATE TABLE IF NOT EXISTS seats (id int NOT NULL AUTO_INCREMENT, seatName VARCHAR(3), reserved BOOLEAN, showtimeID int, FOREIGN KEY(showtimeID) REFERENCES showtimes(id),PRIMARY KEY (id));")){
        qDebug() << "Table seats created!";
        query.exec("TRUNCATE TABLE seats");
        query.exec("INSERT INTO seats (seatName, reserved, showtimeID) VALUES ('E5',1,1),('E6',1,1),('E7',1,1),('E8',1,1),('E9',1,1);");

    }
    else {

        qDebug() << "Table seats failed to create: " << query.lastError().text();
        success = false;

    }

    if (query.exec("CREATE TABLE IF NOT EXISTS staff (staffid int NOT NULL AUTO_INCREMENT, PRIMARY KEY (staffid));")){
        qDebug() << "Table staff created!";
        query.exec("TRUNCATE TABLE staff");
        query.exec("INSERT INTO staff (staffid) VALUES (10000), (10001), (10002)");

    }
    else {

        qDebug() << "Table staff failed to create: " << query.lastError().text();
        success = false;

    }
    if (query.exec("CREATE TABLE IF NOT EXISTS orders (orderid int NOT NULL AUTO_INCREMENT, title VARCHAR(255), screenID int, showtime TIME, seats VARCHAR(255), PRIMARY KEY (orderid));")){
        qDebug() << "Table orders created!";

    }
    else {

        qDebug() << "Table orders failed to create: " << query.lastError().text();
        success = false;

    }
    return success;
}


