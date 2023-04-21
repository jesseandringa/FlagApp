#include "studywindow.h"
#include "ui_studywindow.h"
#include "QCommonStyle"

StudyWindow::StudyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudyWindow)
{
    ui->setupUi(this);

    QCommonStyle style;
    connect(ui->prevCountryArrow, &QToolButton::clicked, this, &StudyWindow::leftArrowClicked);
    connect(ui->nextCountryArrow, &QToolButton::clicked, this, &StudyWindow::rightArrowClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &StudyWindow::backClicked);
}

StudyWindow::~StudyWindow()
{
    delete ui;
}

void StudyWindow::loadCountries()
{
    countries = Country::loadAllCountries();
    displayCountry();
}

void StudyWindow::leftArrowClicked()
{
    if (currentCountry == 0){
        return;
    }
    else {
        currentCountry--;
        displayCountry();
    }
}

void StudyWindow::rightArrowClicked()
{
    if (currentCountry == countries.size() - 1){
        return;
    }
    else {
        currentCountry++;
        displayCountry();
    }
}

void StudyWindow::displayCountry()
{
    country = countries[currentCountry];
    QPixmap flag(country.flagFilename);
    ui->StudyFlagLabel->setPixmap(flag.scaled(ui->StudyFlagLabel->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->studyHintLabel1->setText("\u2022 " + country.facts[0]);
    ui->studyHintLabel2->setText("\u2022 " + country.facts[1]);
    ui->studyHintLabel3->setText("\u2022 " + country.facts[2]);
    ui->studyHintLabel4->setText("\u2022 " + country.facts[3]);
    ui->studyHintLabel5->setText("\u2022 " + country.facts[4]);

}

/// \brief StudyWindow::backClicked
/// Translates a button click to a signal that can be recieved in the mainwindow.
void StudyWindow::backClicked()
{
    emit backToHome();
}
