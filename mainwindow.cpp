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
    connect(this, &MainWindow::checkSignupAttempt, &model,&GameModel::signupAttempt);
    connect(&model, &GameModel::signupFailNotAllFields, this, &MainWindow::signupFailedNotAllFields);
    connect(this, &MainWindow::signupFailedNotAllFieldsFromModel, &signupWindow, &SignUpWindow::signupFailedNotAllFields);
    connect(&model, &GameModel::signupFailPasswordMismatch, this, &MainWindow::signupFailedPassWordMismatch);
    connect(this, &MainWindow::signupFailedPasswordMismatchFromModel, &signupWindow, &SignUpWindow::signupFailedPasswordMismatch);
    connect(&model, &GameModel::signupSuccess, this, &MainWindow::signupSuccess);
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

/// \brief MainWindow::signupFailedPassWordMismatch
/// Relays signal from gamemodel to signupwindow.
void MainWindow::signupFailedPassWordMismatch()
{
    emit signupFailedPasswordMismatchFromModel();
}

void MainWindow::signupSuccess()
{
    signupWindow.close();
    ui->signupButton->setVisible(false);
    ui->loginButton->setVisible(false);
}
