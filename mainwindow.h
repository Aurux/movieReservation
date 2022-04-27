#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "database.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QPushButton>
#include <QSignalMapper>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void selectSeat(QString);

    void on_movieTableView_clicked(const QModelIndex &index);

    void on_screenTableView_clicked(const QModelIndex &index);

private:
    QSignalMapper *signalMapper;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
