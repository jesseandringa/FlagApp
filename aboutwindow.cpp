/// AboutWindow tells the user basic info about how to play from the mainwindow.
/// Written By: name'); DROP TABLE teams;-- ?

#include "aboutwindow.h"
#include "ui_aboutwindow.h"

/// \brief AboutWindow::AboutWindow
/// Constructor
/// \param parent
AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked, this, &AboutWindow::backButtonClicked);

    QPixmap mainGameImage(":/HelpWindowImages/HelpWindowImages/maingame.PNG");
    QPixmap studyImage(":/HelpWindowImages/HelpWindowImages/studyImg.PNG");
    QPixmap statsImage(":/HelpWindowImages/HelpWindowImages/statsImg.PNG");
    ui->mainGameImage->setPixmap(mainGameImage.scaled(ui->mainGameImage->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->studyImage->setPixmap(studyImage.scaled(ui->studyImage->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->statsImage->setPixmap(statsImage.scaled(ui->statsImage->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

/// \brief AboutWindow::~AboutWindow
/// Destructor
AboutWindow::~AboutWindow()
{
    delete ui;
}

/// \brief AboutWindow::backButtonClicked
void AboutWindow::backButtonClicked()
{
    emit returnToMainWindow();
}
