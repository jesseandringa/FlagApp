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
    connect(&signupWindow, &SignUpWindow::signUpAttemptSignal, this, &MainWindow::signUpAttempt);
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

void MainWindow::signupButtonClicked()
{
    signupWindow.show();
}

void MainWindow::signUpAttempt(std::tuple<QString, QString, QString> temp)
{
    QString check = get<0>(temp);
    std::cout << check.toStdString() << std::endl;
    signupWindow.close();
}

