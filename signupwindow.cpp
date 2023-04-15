#include "signupwindow.h"
#include "ui_signupwindow.h"

SignUpWindow::SignUpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpWindow)
{
    ui->setupUi(this);

    connect(ui->signupPushButton, &QPushButton::clicked, this, &SignUpWindow::signUpAttemptSlot);
}

SignUpWindow::~SignUpWindow()
{
    delete ui;
}

void SignUpWindow::signUpAttemptSlot()
{
    auto temp = std::make_tuple(ui->username->text(), ui->password->text(), ui->password2->text());
    emit signUpAttemptSignal(temp);
}
