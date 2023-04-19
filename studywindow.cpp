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
    if (currentCountry == countries.size()){
        return;
    }
    else {
        currentCountry++;
        displayCountry();
    }
}

void StudyWindow::displayCountry()
{

}
