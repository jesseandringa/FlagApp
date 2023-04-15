#include "studywindow.h"
#include "ui_studywindow.h"
#include "QCommonStyle"

StudyWindow::StudyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudyWindow)
{
    ui->setupUi(this);

    QCommonStyle style;
    //ui->pushButton->setIcon(style.standardIcon(QStyle::SP_ArrowBack));
}

StudyWindow::~StudyWindow()
{
    delete ui;
}
