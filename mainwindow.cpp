#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QSqlQueryModel>
#include <QSqlRecord>
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
    ui->movieTableView->setModel(movieModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}







void MainWindow::on_movieTableView_clicked(const QModelIndex &index)
{

}

