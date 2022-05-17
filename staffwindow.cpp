#include "staffwindow.h"
#include "ui_staffwindow.h"
#include "mainwindow.h"
#include <QDir>
StaffWindow::StaffWindow(QWidget *parent, int staffID)
    : QMainWindow(parent)
    , ui(new Ui::StaffWindow)
{
    ui->setupUi(this);
    QString windowTitle = "Movie Reservation - Staff ID: " + QString::number(staffID);
    StaffWindow::setWindowTitle(windowTitle);
    QSqlQueryModel *movieModel = new QSqlQueryModel();
    movieModel->setQuery("SELECT title, runtime, rating FROM movies;");
    movieModel->setHeaderData(0, Qt::Horizontal, tr("Movie"));
    movieModel->setHeaderData(1, Qt::Horizontal, tr("Runtime"));
    movieModel->setHeaderData(2, Qt::Horizontal, tr("Rating"));

    ui->movieTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->movieTableView->setColumnWidth((movieModel->columnCount() -1), 100);
    ui->movieTableView->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->movieTableView->setModel(movieModel);

    qDebug() << "Current dir:" << QDir::currentPath();

    QPixmap pic(":/new/icon/images/film-reel-long.png");
    ui->imageLabel->setPixmap(pic);
    ui->imageLabel->setScaledContents(true);

}

StaffWindow::~StaffWindow()
{
    delete ui;
}


void StaffWindow::on_movieTableView_clicked(const QModelIndex &index)
{
    if (index.column() == 0){

        QString query;
        query = "SELECT screenID, showtime FROM showtimes WHERE title='" + index.data().toString() + "';";
        qDebug() << query;
        QSqlQueryModel * showTimeModel = new QSqlQueryModel();
        showTimeModel->setQuery(query);
        showTimeModel->setHeaderData(0, Qt::Horizontal, tr("Screen"));
        showTimeModel->setHeaderData(1, Qt::Horizontal, tr("Showtime"));

        ui->showingLabel->setText("Showtimes for: " + index.data().toString());
        ui->showingLabel->adjustSize();
        ui->verticalLayout_2->addStretch(1);
        ui->screenTableView->setModel(showTimeModel);
        ui->showingLabel->setEnabled(true);
        ui->screenTableView->setEnabled(true);
        ui->deleteShowtimeBtn->setEnabled(true);
<<<<<<< HEAD
        ui->addShowtimeBtn->setEnabled(true);
        ui->screenLabel->setEnabled(true);
        ui->screenIDText->setEnabled(true);
        ui->showtimeLabel->setEnabled(true);
        ui->showtimeText->setEnabled(true);
=======
>>>>>>> master

        QSqlQuery qry;
        // Get poster/image from database
        qry.prepare("SELECT poster FROM movies WHERE title= :TITLE;");
        qry.bindValue(":TITLE", index.data().toString());
        if(!qry.exec())
            qDebug() << "Error getting poster:\n" << qry.lastError();
        qry.next();
        //QByteArray outByteArray = qry.value(0).toByteArray();
        QPixmap outPixmap = QPixmap(qry.value(0).toString());
        //outPixmap.loadFromData( outByteArray );

        ui->imageLabel->setPixmap( outPixmap );
        ui->imageLabel->setScaledContents(true);

       }
    else {
        StaffWindow::on_movieTableView_clicked(index.siblingAtColumn(0));
    }


}

void clear(QLayout *layout) {
    // Function sourced from https://stackoverflow.com/questions/4857188/clearing-a-layout-in-qt
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clear(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}


void StaffWindow::on_backBtn_clicked()
{

    MainWindow *w = new MainWindow;
    w->show();
    this->close();
}


void StaffWindow::on_deleteMovieBtn_clicked()
{
    QString movie = ui->movieTableView->selectionModel()->selectedRows().at(0).data().toString();

    qDebug() << "Movie to be deleted: " + movie;

    QSqlQuery query;
    query.prepare("DELETE FROM movies WHERE title= :TITLE;");
    query.bindValue(":TITLE",movie);
    if (query.exec()){
        qDebug() << movie + " deleted successfully!";
        QSqlQueryModel *movieModel = new QSqlQueryModel();
        movieModel->setQuery("SELECT title, runtime, rating FROM movies;");
        ui->movieTableView->setModel(movieModel);
        ui->screenTableView->setModel(NULL);
        ui->showingLabel->setText("Showtimes");
        QPixmap pic(":/new/icon/images/film-reel-long.png");
        ui->imageLabel->setPixmap(pic);
        ui->showingLabel->setEnabled(false);
        ui->screenTableView->setEnabled(false);
        ui->deleteShowtimeBtn->setEnabled(false);
<<<<<<< HEAD
        ui->addShowtimeBtn->setEnabled(false);
        ui->screenLabel->setEnabled(false);
        ui->screenIDText->setEnabled(false);
        ui->showtimeLabel->setEnabled(false);
        ui->showtimeText->setEnabled(false);

=======
>>>>>>> master
    }
    else qDebug() << "Movie failed to delete.";



}


void StaffWindow::on_deleteShowtimeBtn_clicked()
{
    QString showtime = ui->screenTableView->selectionModel()->selectedRows().at(0).siblingAtColumn(1).data().toString();
    int screenID = ui->screenTableView->selectionModel()->selectedRows().at(0).data().toInt();

    QSqlQuery query;
    query.prepare("SET foreign_key_checks = 0; DELETE FROM showtimes WHERE screenID= :SCREENID AND showtime= :SHOWTIME;");
    query.bindValue(":SCREENID", screenID);
    query.bindValue(":SHOWTIME", showtime);
    if (query.exec()){
        QString query;
        query = "SELECT screenID, showtime FROM showtimes WHERE title='" + ui->movieTableView->selectionModel()->selectedRows().at(0).data().toString() + "';";
        qDebug() << query;
        QSqlQueryModel * showTimeModel = new QSqlQueryModel();
        showTimeModel->setQuery(query);
        ui->screenTableView->setModel(showTimeModel);
    }
    else {
        qDebug() << "Showtime failed to delete.";
        qDebug() << query.lastError();
    }
}

<<<<<<< HEAD

void StaffWindow::on_addMovieBtn_clicked()
{
    QString title;
    QString runtime;
    QString rating;

    title=ui->movieText->text();
    runtime=ui->runtimeText->text();
    rating=ui->ratingText->text();

    QSqlQuery query;
    query.prepare("INSERT INTO movies (title, runtime, rating) VALUES(:TITLE, :RUNTIME, :RATING)");
    query.bindValue(":TITLE",title);
    query.bindValue(":RUNTIME",runtime);
    query.bindValue(":RATING",rating);
    if (query.exec()){
        qDebug() << query.lastError();
        QSqlQueryModel *movieModel = new QSqlQueryModel();
        movieModel->setQuery("SELECT title, runtime, rating FROM movies;");
        ui->movieTableView->setModel(movieModel);
    }
    else qDebug() << query.lastError();

}


void StaffWindow::on_addShowtimeBtn_clicked()
{
    QString showtimes = ui->screenTableView->selectionModel()->selectedRows().at(0).siblingAtColumn(1).data().toString();
    QString movie = ui->movieTableView->selectionModel()->selectedRows().at(0).data().toString();

    QString screen;
    QString showtime;

    showtime=ui->showtimeText->text();
    screen=ui->screenIDText->text();

    QSqlQuery query;
    query.prepare("INSERT INTO showtimes (screenID, showtime, movie) VALUES(:SCREEN, :SHOWTIME, :MOVIE) WHERE showtime = :SHOWTIMES;");
    query.bindValue(":SHOWTIME", showtime);
    query.bindValue(":SCREEN", screen);
    query.bindValue(":SHOWTIMES", showtimes);
    query.bindValue(":MOVIE", movie);
    if (query.exec()){
        QString query;
        query = "SELECT screenID, showtime FROM showtimes WHERE title='" + ui->movieTableView->selectionModel()->selectedRows().at(0).data().toString() + "';";
        qDebug() << query;
        QSqlQueryModel * showTimeModel = new QSqlQueryModel();
        showTimeModel->setQuery(query);
        ui->screenTableView->setModel(showTimeModel);
    }
    else qDebug() << query.lastError();
         qDebug() << "Showtime failed to add.";
}

=======
>>>>>>> master
