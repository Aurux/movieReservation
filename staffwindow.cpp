#include "staffwindow.h"
#include "ui_staffwindow.h"
#include <QDir>
StaffWindow::StaffWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StaffWindow)
{
    ui->setupUi(this);
    StaffWindow::setWindowTitle("Movie Reservation");
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

