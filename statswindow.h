#ifndef STATSWINDOW_H
#define STATSWINDOW_H

#include <QDialog>
#include <iostream>
using std::array;

namespace Ui {
class StatsWindow;
}

class StatsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StatsWindow(QWidget *parent = nullptr);
    ~StatsWindow();

public slots:
    void receiveStats(array<int, 6> stats);

private:
    Ui::StatsWindow *ui;
};

#endif // STATSWINDOW_H
