#ifndef STAFFWINDOW_H
#define STAFFWINDOW_H

#include <QMainWindow>
#include "database.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QPushButton>
#include <QSignalMapper>
#include <QPixmap>
#include <QMessageBox>
#include <QUuid>
#include <QModelIndex>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui { class StaffWindow; }
QT_END_NAMESPACE

class StaffWindow : public QMainWindow
{
    Q_OBJECT

public:
    StaffWindow(QWidget *parent = nullptr);
    ~StaffWindow();

private slots:

    void on_movieTableView_clicked(const QModelIndex &index);

private:
    QSignalMapper *signalMapper;
    Ui::StaffWindow *ui;
};
#endif // STAFFWINDOW_H
