#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QDialog>
#include <tuple>

namespace Ui {
class SignUpWindow;
}

class SignUpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpWindow(QWidget *parent = nullptr);
    ~SignUpWindow();
public slots:
    void signUpAttemptSlot();
    void signupFailedNotAllFields();
    void signupFailedUserExists();
    void signupFailedPasswordMismatch();

signals:
    void signUpAttemptSignal(std::tuple<QString, QString, QString>);

private:
    Ui::SignUpWindow *ui;
};

#endif // SIGNUPWINDOW_H
