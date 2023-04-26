#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked, this, &AboutWindow::backButtonClicked);

    QPixmap mainGameImage(":/HelpWindowImages/HelpWindowImages/feedback.PNG");
    QPixmap difficultyImage(":/HelpWindowImages/HelpWindowImages/GuessArea.PNG");
    QPixmap studyImage(":/HelpWindowImages/HelpWindowImages/hintarea.PNG");
    QPixmap statsImage(":/HelpWindowImages/HelpWindowImages/hintarea.PNG");
    ui->mainGameImage->setPixmap(mainGameImage.scaled(ui->mainGameImage->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->difficultyImage->setPixmap(difficultyImage.scaled(ui->difficultyImage->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->studyImage->setPixmap(studyImage.scaled(ui->studyImage->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->statsImage->setPixmap(statsImage.scaled(ui->statsImage->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::backButtonClicked()
{
    emit returnToMainWindow();
}
