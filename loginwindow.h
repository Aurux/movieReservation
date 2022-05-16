#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "staffwindow.h"
#include <QDialog>

namespace Ui {
class loginWindow;
}

class loginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit loginWindow(QWidget *parent = nullptr);
    ~loginWindow();

private slots:

    void on_loginPushButton_clicked();

private:
    Ui::loginWindow *ui;
    StaffWindow *staffWindow;
};

#endif // LOGINWINDOW_H
