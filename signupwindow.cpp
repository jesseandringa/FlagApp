/// SignupWindow implements the user interface for the signupwindow.
/// The logic for signing up is handled by UserDataHandler.
/// Written By: name'); DROP TABLE teams;-- ?

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
    ui->username->setFocus();

    connect(ui->signupPushButton, &QPushButton::clicked, this, &SignUpWindow::signUpAttemptSlot);
    connect(ui->username, &QLineEdit::returnPressed, this, &SignUpWindow::signUpAttemptSlot);
    connect(ui->password, &QLineEdit::returnPressed, this, &SignUpWindow::signUpAttemptSlot);
    connect(ui->password2, &QLineEdit::returnPressed, this, &SignUpWindow::signUpAttemptSlot);
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

/// \brief SignUpWindow::signupFailedNotAllFields SLOT
void SignUpWindow::signupFailedNotAllFields()
{
    ui->signupLabel->setText("Enter All Fields:");
}

/// \brief SignUpWindow::signupFailedUserExists SLOT
void SignUpWindow::signupFailedUserExists()
{
    ui->signupLabel->setText("User Already Exists:");
}

/// \brief SignUpWindow::signupFailedPasswordMismatch SLOT
void SignUpWindow::signupFailedPasswordMismatch()
{
    ui->signupLabel->setText("Password Mismatch:");
}


/// \brief SignUpWindow::signupFailedSpacesDetected SLOT
void SignUpWindow::signupFailedSpacesDetected()
{
    ui->signupLabel->setText("No Spaces Allowed:");
}
