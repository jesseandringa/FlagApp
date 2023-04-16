#include "signupwindow.h"
#include "ui_signupwindow.h"

/// \brief SignUpWindow::SignUpWindow
/// Constructor
/// \param parent
SignUpWindow::SignUpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpWindow)
{
    ui->setupUi(this);

    connect(ui->signupPushButton, &QPushButton::clicked, this, &SignUpWindow::signUpAttemptSlot);
}

/// \brief SignUpWindow::~SignUpWindow
/// Destructor
SignUpWindow::~SignUpWindow()
{
    delete ui;
}

/// \brief SignUpWindow::signUpAttemptSlot
/// Converts button click to a signal with the user sign up info.
void SignUpWindow::signUpAttemptSlot()
{
    auto temp = std::make_tuple(ui->username->text(), ui->password->text(), ui->password2->text());
    emit signUpAttemptSignal(temp);
}

/// \brief SignUpWindow::signupFailedNotAllFields
void SignUpWindow::signupFailedNotAllFields()
{
    ui->signupLabel->setText("Enter All Fields:");
}

/// \brief SignUpWindow::signupFailedUserExists
void SignUpWindow::signupFailedUserExists()
{
    ui->signupLabel->setText("User Already Exists:");
}

/// \brief SignUpWindow::signupFailedPasswordMismatch
void SignUpWindow::signupFailedPasswordMismatch()
{
    ui->signupLabel->setText("Password Mismatch:");
}
