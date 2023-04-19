#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <iostream>
#include "country.h"
#include "gamemodel.h"

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
//    explicit GameWindow(QWidget *parent = nullptr);
    explicit GameWindow(GameModel &model,QWidget *parent = nullptr);
    ~GameWindow();

    void initNewGame(int difficulty);

private slots:
    void on_currentGuess_returnPressed();
    void receiveCurrentGuessInfo(std::string guess, int guessNum, double distance, std::vector<QString> hints, std::string dir);
    void on_guessButton_clicked();
    void setUIforNewCountry(QString filepath, QString fact1);
    void winScreen();

private:
    Ui::GameWindow *ui;
signals:
    void newGuess(std::string currGuess);
    void newGame(int difficulty);

};

#endif // GAMEWINDOW_H
