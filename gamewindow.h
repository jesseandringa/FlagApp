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
    explicit GameWindow(GameModel &model,QWidget *parent = nullptr);
    ~GameWindow();

    void initNewGame(int difficulty);
    void makeWidgetsVisibleAndEnabled(QWidget *widget);

private slots:
    void on_currentGuess_returnPressed();
    void receiveCurrentGuessInfo(std::string guess, int guessNum, double distance, std::vector<QString> hints, std::string dir);
    void on_guessButton_clicked();
    void setUIforNewCountry(QString filepath, QString fact1);
    void winScreen();
    void on_nextFlag_clicked();
    void invalidGuessSlot();

    void on_QuitButton_clicked();

    void on_currentGuess_textChanged(const QString &arg1);

private:
    Ui::GameWindow *ui;
    void hideWinScreen();
    void userGuessed();
    void clearHintsAndGuesses();
    void addSuggestions(std::vector<string> suggestions);

signals:
    void newGuess(std::string currGuess);
    void newGame(int difficulty);
    void nextCountry();
    void userTypingAndNeedsSuggestions(string currentText);

};

#endif // GAMEWINDOW_H
