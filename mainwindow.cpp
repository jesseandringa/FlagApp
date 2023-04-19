#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow (GameModel &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      gameWindow(model)
{

    ui->setupUi(this);
    ui->easyButton->setVisible(false);
    ui->mediumButton->setVisible(false);
    ui->hardButton->setVisible(false);

    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::playButtonClicked);
    connect(ui->studyButton, &QPushButton::clicked, this, &MainWindow::studyButtonClicked);

    connect(ui->easyButton, &QPushButton::clicked, this, &MainWindow::easyDifficultyClicked);
    connect(ui->mediumButton, &QPushButton::clicked, this, &MainWindow::mediumDifficultyClicked);
    connect(ui->hardButton, &QPushButton::clicked, this, &MainWindow::hardDifficultyClicked);

    connect(ui->signupButton, &QPushButton::clicked, this, &MainWindow::signupButtonClicked);
    connect(&signupWindow, &SignUpWindow::signUpAttemptSignal, this, &MainWindow::signupAttempt);
    connect(this, &MainWindow::checkSignupAttempt, &userdatahandler, &UserDataHandler::signupAttempt);
    connect(&userdatahandler, &UserDataHandler::signupFailNotAllFields, this, &MainWindow::signupFailedNotAllFields);
    connect(this, &MainWindow::signupFailedNotAllFieldsFromModel, &signupWindow, &SignUpWindow::signupFailedNotAllFields);
    connect(&userdatahandler, &UserDataHandler::signupFailUserExists, this, &MainWindow::signupFailedUserExists);
    connect(this, &MainWindow::signupFailedUserExistsFromModel, &signupWindow, &SignUpWindow::signupFailedUserExists);
    connect(&userdatahandler, &UserDataHandler::signupFailPasswordMismatch, this, &MainWindow::signupFailedPassWordMismatch);
    connect(this, &MainWindow::signupFailedPasswordMismatchFromModel, &signupWindow, &SignUpWindow::signupFailedPasswordMismatch);
    connect(&userdatahandler, &UserDataHandler::signupSuccess, this, &MainWindow::signupSuccess);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginButtonClicked);
    connect(&loginwindow, &LoginWindow::loginAttempt, this, &MainWindow::loginAttemptSlot);
    connect(this, &MainWindow::loginAttempt, &userdatahandler, &UserDataHandler::loginAttempt);
    connect(&userdatahandler, &UserDataHandler::loginFailedNotAllFields, this, &MainWindow::loginFailedNotALlFieldsSlot);
    connect(this, &MainWindow::loginFailedNotAllFields, &loginwindow, &LoginWindow::loginFailedNotAllFieldsSlot);
    connect(&userdatahandler, &UserDataHandler::loginFailedDNE, this, &MainWindow::loginFailedUserDNESlot);
    connect(this, &MainWindow::loginFailedUserDNE, &loginwindow, &LoginWindow::loginFailedUserDNESlot);
    connect(&userdatahandler, &UserDataHandler::loginSuccessful, this, &MainWindow::loginSuccessfulSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playButtonClicked()
{
    ui->playButton->setVisible(false);
    ui->studyButton->setVisible(false);
    ui->helpButton->setVisible(false);
    ui->easyButton->setVisible(true);
    ui->mediumButton->setVisible(true);
    ui->hardButton->setVisible(true);
}

void MainWindow::studyButtonClicked()
{
    this->close();
    //have the countries load into a an array in study
    studyWindow.show();
}

void MainWindow::helpButtonClicked()
{

}

void MainWindow::easyDifficultyClicked()
{
    this->close();
    gameWindow.initNewGame(0);
    gameWindow.show();
}

void MainWindow::mediumDifficultyClicked()
{
    this->close();
    gameWindow.initNewGame(1);
    gameWindow.show();
}

void MainWindow::hardDifficultyClicked()
{
    this->close();
    gameWindow.initNewGame(2);
    gameWindow.show();
}

/// \brief MainWindow::signupButtonClicked
/// Let the user sign in
void MainWindow::signupButtonClicked()
{
    signupWindow.show();
}

/// \brief MainWindow::signupAttempt
/// Relays signal from the signupwindow to the gameModel
/// \param temp
void MainWindow::signupAttempt(std::tuple<QString, QString, QString> temp)
{
    auto[username, password, passwordCheck] = temp;
    emit checkSignupAttempt(username, password, passwordCheck);
}

/// \brief MainWindow::signupFailedNotAllFields
/// Relays signal from gamemodel to the signupwindow.
void MainWindow::signupFailedNotAllFields()
{
    emit signupFailedNotAllFieldsFromModel();
}

/// \brief MainWindow::signupFailedUserExists
void MainWindow::signupFailedUserExists()
{
    emit signupFailedUserExistsFromModel();
}

/// \brief MainWindow::signupFailedPassWordMismatch
/// Relays signal from gamemodel to signupwindow.
void MainWindow::signupFailedPassWordMismatch()
{
    emit signupFailedPasswordMismatchFromModel();
}

/// \brief MainWindow::signupSuccess
void MainWindow::signupSuccess()
{
    signupWindow.close();
    ui->signupButton->setVisible(false);
    ui->loginButton->setVisible(false);
}

/// \brief MainWindow::loginButtonPressed
/// Makes the loginwindow visible.
void MainWindow::loginButtonClicked()
{
    loginwindow.show();
}

/// \brief LoginWindow::loginAttemptSlot
/// Passes username and password along to the model.
/// \param username
/// \param password
void MainWindow::loginAttemptSlot(QString username, QString password)
{
    emit loginAttempt(username, password);
}

/// \brief MainWindow::loginFailedNotALlFieldsSlot
void MainWindow::loginFailedNotALlFieldsSlot()
{
    emit loginFailedNotAllFields();
}

/// \brief MainWindow::loginFailedUserDNESlot
void MainWindow::loginFailedUserDNESlot()
{
    emit loginFailedUserDNE();
}

/// \brief MainWindow::loginSuccessfulSlot
void MainWindow::loginSuccessfulSlot()
{
    loginwindow.close();
}
