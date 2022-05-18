#ifndef DBSETUPWINDOW_H
#define DBSETUPWINDOW_H

#include <QDialog>
#include "database.h"
#include "qabstractbutton.h"
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



    void on_exampleDataBtn_clicked();


    void on_buttonBox_2_clicked(QAbstractButton *button);

    void on_passInput_textChanged(const QString &arg1);

    void on_userInput_textChanged(const QString &arg1);

    void on_hostInput_textChanged(const QString &arg1);



    void on_clearDBBtn_clicked();

private:
    Ui::DBSetupWindow *ui;
};

#endif // DBSETUPWINDOW_H
