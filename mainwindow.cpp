#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow (GameModel &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      gameWindow(model)
{

    ui->setupUi(this);
    this->statusBar()->setSizeGripEnabled(false);
    this->centralWidget()->setStyleSheet("background-image:url(:/backgroundImages/BackgroundImages/earthImage.jpg); background-position: center;");
    ui->easyButton->setVisible(false);
    ui->mediumButton->setVisible(false);
    ui->hardButton->setVisible(false);
    ui->backButton->setVisible(false);
    ui->statsButton->setVisible(false);
    ui->statsButton->setEnabled(false);

    ui->easyButton->setStyleSheet("color: white;");
    ui->mediumButton->setStyleSheet("color: white;");
    ui->hardButton->setStyleSheet("color: white;");
    ui->playButton->setStyleSheet("color: white;");
    ui->studyButton->setStyleSheet("color: white;");
    ui->helpButton->setStyleSheet("color: white;");
    ui->backButton->setStyleSheet("color: white;");
    ui->signupButton->setStyleSheet("color: white;");
    ui->loginButton->setStyleSheet("color: white;");
    ui->statsButton->setStyleSheet("color: white;");




    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::playButtonClicked);
    connect(ui->studyButton, &QPushButton::clicked, this, &MainWindow::studyButtonClicked);
    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::helpButtonClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::backButtonClicked);

    connect(ui->easyButton, &QPushButton::clicked, this, &MainWindow::easyDifficultyClicked);
    connect(ui->mediumButton, &QPushButton::clicked, this, &MainWindow::mediumDifficultyClicked);
    connect(ui->hardButton, &QPushButton::clicked, this, &MainWindow::hardDifficultyClicked);

    connect(ui->signupButton, &QPushButton::clicked, this, &MainWindow::signupButtonClicked);
    connect(&signupWindow, &SignUpWindow::signUpAttemptSignal, this, &MainWindow::signupAttemptSlot);
    connect(this, &MainWindow::checkSignupAttempt, &userdatahandler, &UserDataHandler::signupAttempt);
    connect(&userdatahandler, &UserDataHandler::signupFailNotAllFields, this, &MainWindow::signupFailedNotAllFieldsSlot);
    connect(this, &MainWindow::signupFailedNotAllFields, &signupWindow, &SignUpWindow::signupFailedNotAllFields);
    connect(&userdatahandler, &UserDataHandler::signupFailUserExists, this, &MainWindow::signupFailedUserExistsSlot);
    connect(this, &MainWindow::signupFailedUserExists, &signupWindow, &SignUpWindow::signupFailedUserExists);
    connect(&userdatahandler, &UserDataHandler::signupFailPasswordMismatch, this, &MainWindow::signupFailedPassWordMismatchSlot);
    connect(this, &MainWindow::signupFailedPasswordMismatch, &signupWindow, &SignUpWindow::signupFailedPasswordMismatch);
    connect(&userdatahandler, &UserDataHandler::signupFailSpacesDetected, this, &MainWindow::signupFailedSpacesDetectedSlot);
    connect(this, &MainWindow::signupFailedSpacesDetected, &signupWindow, &SignUpWindow::signupFailedSpacesDetected);
    connect(&userdatahandler, &UserDataHandler::signupSuccess, this, &MainWindow::signupSuccessSlot);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginButtonClicked);
    connect(&loginwindow, &LoginWindow::loginAttempt, this, &MainWindow::loginAttemptSlot);
    connect(this, &MainWindow::loginAttempt, &userdatahandler, &UserDataHandler::loginAttempt);
    connect(&userdatahandler, &UserDataHandler::loginFailedNotAllFields, this, &MainWindow::loginFailedNotALlFieldsSlot);
    connect(this, &MainWindow::loginFailedNotAllFields, &loginwindow, &LoginWindow::loginFailedNotAllFieldsSlot);
    connect(&userdatahandler, &UserDataHandler::loginFailedDNE, this, &MainWindow::loginFailedUserDNESlot);
    connect(this, &MainWindow::loginFailedUserDNE, &loginwindow, &LoginWindow::loginFailedUserDNESlot);
    connect(&userdatahandler, &UserDataHandler::loginSuccessful, this, &MainWindow::loginSuccessfulSlot);

    connect(ui->statsButton, &QPushButton::clicked, this, &MainWindow::statsClicked);
    connect(this, &MainWindow::getStats, &userdatahandler, &UserDataHandler::statsRequest);
    connect(&userdatahandler, &UserDataHandler::sendStats, this, &MainWindow::statsReceived);
    connect(this, &MainWindow::sendStats, &statswindow, &StatsWindow::receiveStats);

    connect(&model, &GameModel::countryFinished, this, &MainWindow::countryFinishedSlot);
    connect(this, &MainWindow::countryFinished, &userdatahandler, &UserDataHandler::countryFinished);
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
    ui->backButton->setVisible(true);
    ui->easyButton->setVisible(true);
    ui->mediumButton->setVisible(true);
    ui->hardButton->setVisible(true);
}

void MainWindow::studyButtonClicked()
{
    this->close();
    studyWindow.loadCountries();
    studyWindow.show();
}

void MainWindow::helpButtonClicked()
{

}

void MainWindow::backButtonClicked()
{
    ui->playButton->setVisible(true);
    ui->studyButton->setVisible(true);
    ui->helpButton->setVisible(true);
    ui->backButton->setVisible(false);
    ui->easyButton->setVisible(false);
    ui->mediumButton->setVisible(false);
    ui->hardButton->setVisible(false);
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
void MainWindow::signupAttemptSlot(std::tuple<QString, QString, QString> temp)
{
    auto[username, password, passwordCheck] = temp;
    emit checkSignupAttempt(username, password, passwordCheck);
}

/// \brief MainWindow::signupFailedNotAllFields
/// Relays signal from gamemodel to the signupwindow.
void MainWindow::signupFailedNotAllFieldsSlot()
{
    emit signupFailedNotAllFields();
}

/// \brief MainWindow::signupFailedUserExists
void MainWindow::signupFailedUserExistsSlot()
{
    emit signupFailedUserExists();
}

/// \brief MainWindow::signupFailedPassWordMismatch
/// Relays signal from gamemodel to signupwindow.
void MainWindow::signupFailedPassWordMismatchSlot()
{
    emit signupFailedPasswordMismatch();
}


/// \brief MainWindow::signupFailedSpacesDetectedSlot
void MainWindow::signupFailedSpacesDetectedSlot()
{
    emit signupFailedSpacesDetected();
}

/// \brief MainWindow::signupSuccessSlot
void MainWindow::signupSuccessSlot()
{
    signupWindow.close();
    ui->signupButton->setVisible(false);
    ui->loginButton->setVisible(false);
    ui->statsButton->setVisible(true);
    ui->statsButton->setEnabled(true);
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
    ui->signupButton->setVisible(false);
    ui->loginButton->setVisible(false);
    ui->statsButton->setVisible(true);
    ui->statsButton->setEnabled(true);
}

/// \brief MainWindow::statsClicked
void MainWindow::statsClicked()
{
    emit getStats();
}

/// \brief MainWindow::statsReceived
/// \param stats
void MainWindow::statsReceived(std::array<int, 6> stats)
{
    emit sendStats(stats);
    statswindow.show();
}

/// \brief MainWindow::countryFinishedSlot
/// \param finishPosition
void MainWindow::countryFinishedSlot(int finishPosition)
{
    emit countryFinished(finishPosition);
}
