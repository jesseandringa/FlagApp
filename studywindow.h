#ifndef STUDYWINDOW_H
#define STUDYWINDOW_H

#include <QWidget>

namespace Ui {
class StudyWindow;
}

class StudyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudyWindow(QWidget *parent = nullptr);
    ~StudyWindow();

private:
    Ui::StudyWindow *ui;
};

#endif // STUDYWINDOW_H
