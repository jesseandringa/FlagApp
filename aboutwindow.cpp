#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    connect(ui->backButton, QPushButton::clicked, this, AboutWindow::backButtonClicked);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::backButtonClicked()
{
    emit returnToMainWindow();
}
