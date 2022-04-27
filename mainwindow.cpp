#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
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

    qDebug() << "Current dir:" << QDir::currentPath();


    QPixmap pic(":/new/icon/images/film-reel.png");
    ui->imageLabel->setPixmap(pic);
    ui->imageLabel->setScaledContents(true);

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
        ui->showingLabel->setEnabled(true);
        ui->screenTableView->setEnabled(true);
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

int selectedSeats = 0;
void MainWindow::selectSeat(QString position) {
    QStringList query = position.split(",");
    qDebug() << "Button pushed at: " << query.at(0).toInt() << "," << query.at(1).toInt() << " Screen: " << query.at(2).toInt() << "Seat: " << query.at(3);
    selectedSeats += 1;
    ui->selectedLabel->setText("Selected seats: " + QString::number(selectedSeats));
}



void MainWindow::on_screenTableView_clicked(const QModelIndex &index)
{
    if (index.column() == 0){
        ui->selectedLabel->setEnabled(true);
        ui->reserveButton->setEnabled(true);
        ui->seatLabel->setEnabled(true);
        clearLayout(ui->seatGridLayout); // Make sure seat grid is clear.
        ui->seatLabel->setText("Screen: " + index.data().toString());
        QSignalMapper *signalMapper = new QSignalMapper(ui->seatGridLayout);

        QSqlQuery query;


        query.exec("SELECT totalSeats FROM screens WHERE screenID='" + index.data().toString() + "';");
        int rows = 0;
        int columns = 16;


        if (query.next()) {
            if (query.value(0).toInt() < 100) {
                columns = 8;
            }
            rows = query.value(0).toInt() / columns;
        }





        QString rowChars = "ABCDEFGHIJKLMOPQRSTUVWXYZ";
        for (int i = 0; i < rows; i++){
            int colNum = 1;
            for (int j = 0; j < columns; j++){
                // Generate seat button
                QPushButton * button = new QPushButton(this);
                QString buttonText = rowChars[i] + QString::number(j + 1);
                button->setText(buttonText);
                button->setCheckable(true);
                ui->seatGridLayout->addWidget(button, i, j);

                QString args= QString("%1,%2,%3,%4").arg(i).arg(j).arg(index.data().toString()).arg(buttonText);
                connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
                signalMapper->setMapping(button, args);

                colNum++;
            }

        }

        connect(signalMapper, SIGNAL(mappedString(QString)), this, SLOT(selectSeat(QString)));

    }
}


