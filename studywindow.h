#ifndef STUDYWINDOW_H
#define STUDYWINDOW_H

#include <QWidget>
#include "country.h"

namespace Ui {
class StudyWindow;
}

class StudyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudyWindow(QWidget *parent = nullptr);
    ~StudyWindow();
    void loadCountries();


public slots:
  void leftArrowClicked();
  void rightArrowClicked();
  void backClicked();

signals:
  void backToHome();

private:
    Ui::StudyWindow *ui;
    std::vector<Country> countries;
    Country country;
    int currentCountry = 0;
    void displayCountry();
};

#endif // STUDYWINDOW_H
