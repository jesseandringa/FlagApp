#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <iostream>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    connect(ui->loginPushButton, &QPushButton::clicked, this, &LoginWindow::loginAttemptSlot);
    connect(ui->username, &QLineEdit::returnPressed, this, &LoginWindow::loginAttemptSlot);
    connect(ui->password, &QLineEdit::returnPressed, this, &LoginWindow::loginAttemptSlot);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

/// \brief LoginWindow::loginAttempt
/// Receives a signal from the push button and emits one with the login info.
void LoginWindow::loginAttemptSlot()
{
    emit loginAttempt(ui->username->text(), ui->password->text());
}

/// \brief LoginWindow::loginFailedNotAllFieldsSlot
void LoginWindow::loginFailedNotAllFieldsSlot()
{
    ui->label->setText("Complete all fields: ");
}

void LoginWindow::loginFailedUserDNESlot()
{
    ui->label->setText("Incorrect username or password:");
}
