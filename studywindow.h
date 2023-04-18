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

private slots:

private:
    Ui::StudyWindow *ui;
    static std::vector<Country> loadCountries();
    int currentCountry = 0;
};

#endif // STUDYWINDOW_H
