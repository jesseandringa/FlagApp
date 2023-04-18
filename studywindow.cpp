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

void StudyWindow::on_nextCountryArrow_pressed()
{
    currentCountry++;
    ui->studyHintLabel1->setText("");
    ui->studyHintLabel2->setText("");
    ui->studyHintLabel3->setText("");
    ui->studyHintLabel4->setText("");
    ui->studyHintLabel5->setText("");
}


void StudyWindow::on_prevCountryArrow_pressed()
{
    currentCountry--;
    ui->studyHintLabel1->setText("");
    ui->studyHintLabel2->setText("");
    ui->studyHintLabel3->setText("");
    ui->studyHintLabel4->setText("");
    ui->studyHintLabel5->setText("");
}

