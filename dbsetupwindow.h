#ifndef DBSETUPWINDOW_H
#define DBSETUPWINDOW_H

#include <QDialog>
#include "database.h"
namespace Ui {
class DBSetupWindow;
}

class DBSetupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DBSetupWindow(QWidget *parent = nullptr);
    ~DBSetupWindow();

private slots:
    void on_testConnBtn_clicked();

    void on_createDBBtn_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DBSetupWindow *ui;
};

#endif // DBSETUPWINDOW_H
