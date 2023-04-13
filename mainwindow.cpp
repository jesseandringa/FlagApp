#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->easyButton->setVisible(false);
    ui->mediumButton->setVisible(false);
    ui->hardButton->setVisible(false);

    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::playButtonClicked);

    connect(ui->easyButton, &QPushButton::clicked, this, &MainWindow::easyDifficultyClicked);
    connect(ui->mediumButton, &QPushButton::clicked, this, &MainWindow::mediumDifficultyClicked);
    connect(ui->hardButton, &QPushButton::clicked, this, &MainWindow::hardDifficultyClicked);

    connect(ui->signupButton, &QPushButton::clicked, this, &MainWindow::signupButtonClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playButtonClicked()
{
    ui->playButton->setVisible(false);
    ui->playButton->setVisible(false);
    ui->playButton->setVisible(false);
    ui->easyButton->setVisible(true);
    ui->mediumButton->setVisible(true);
    ui->hardButton->setVisible(true);
}

void MainWindow::studyButtonClicked()
{

}

void MainWindow::helpButtonClicked()
{

}

void MainWindow::easyDifficultyClicked()
{
    this->close();
    //this signal emits to logic model for game
    emit showWindowDifficultyChosen("EASY");
    gameWindow.show();
}

void MainWindow::mediumDifficultyClicked()
{
    this->close();
    //this signal emits to logic model for game
    emit showWindowDifficultyChosen("MEDIUM");
    gameWindow.show();
}

void MainWindow::hardDifficultyClicked()
{
    this->close();
    emit showWindowDifficultyChosen("HARD");
    gameWindow.show();
}

void MainWindow::signupButtonClicked()
{
    signupWindow.show();
}



