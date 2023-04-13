#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <iostream>
#include "country.h"

using std::cout;
using std::endl;

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    std::vector<Country> countries;

    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void initNewGame(int difficulty);

private:
    Ui::GameWindow *ui;

};

#endif // GAMEWINDOW_H
