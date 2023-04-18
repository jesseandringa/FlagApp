#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

public slots:
    void loginAttemptSlot();
    void loginFailedNotAllFieldsSlot();
    void loginFailedUserDNESlot();

signals:
    void loginAttempt(QString, QString);


private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
