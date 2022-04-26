#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setWindowTitle("Movie Reservation");
    QSqlQueryModel *movieModel = new QSqlQueryModel();
    movieModel->setQuery("SELECT title, runtime, rating FROM movies;");
    movieModel->setHeaderData(0, Qt::Horizontal, tr("Movie"));
    movieModel->setHeaderData(1, Qt::Horizontal, tr("Runtime"));
    movieModel->setHeaderData(2, Qt::Horizontal, tr("Rating"));


    ui->movieTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->movieTableView->setColumnWidth((movieModel->columnCount() -1), 100);
    ui->movieTableView->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->movieTableView->setModel(movieModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}







void MainWindow::on_movieTableView_clicked(const QModelIndex &index)
{
    if (index.column() == 0){
        QString query;
        query = "SELECT screenID, showtime FROM movieScreen WHERE title='" + index.data().toString() + "';";
        qDebug() << query;
        QSqlQueryModel * showTimeModel = new QSqlQueryModel();
        showTimeModel->setQuery(query);
        showTimeModel->setHeaderData(0, Qt::Horizontal, tr("Screen"));
        showTimeModel->setHeaderData(1, Qt::Horizontal, tr("Showtime"));

        ui->showingLabel->setText("Showtimes for: " + index.data().toString());
        ui->showingLabel->adjustSize();
        ui->verticalLayout_2->addStretch(1);
        ui->screenTableView->setModel(showTimeModel);
       }

}

void clearLayout(QLayout *layout) {
    // Function sourced from https://stackoverflow.com/questions/4857188/clearing-a-layout-in-qt
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void MainWindow::on_screenTableView_clicked(const QModelIndex &index)
{
    if (index.column() == 0){
        clearLayout(ui->seatGridLayout);
        ui->seatLabel->setText("Screen: " + index.data().toString());
        QSqlQuery query;
        query.exec("SELECT totalSeats FROM screens WHERE screenID='" + index.data().toString() + "';");
        int rows = 0;
        int columns = 16;

        if (query.next()) {
            rows = query.value(0).toInt() / columns;
        }





        QString rowChars = "ABCDEFGHIJKLMOPQRSTUVWXYZ";
        for (int i = 0; i < rows; i++){
            int colNum = 1;
            for (int j = 0; j < columns; j++){
                QPushButton * button = new QPushButton(this);
                qDebug() << "Making seat: " << rowChars[i] << QString::number(j + 1);
                button->setText(rowChars[i] + QString::number(j + 1));
                button->setCheckable(true);
                ui->seatGridLayout->addWidget(button, i, j);
                colNum++;
            }

        }

    }
}

