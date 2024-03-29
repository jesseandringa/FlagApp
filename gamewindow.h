/// GameWindow handles the UI side of gameplay.  It registers users input, emits it
/// to the GameModel and then recieves an emit from the GameModel to update the users screen.
/// Written By: name'); DROP TABLE teams;-- ?

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <iostream>
#include "QtWidgets/qlistwidget.h"
#include "country.h"
#include "gamemodel.h"
#include "gamewindowhelp.h"
#include <QTimer>


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
    void winScreen(QString country);
    void lossScreen(QString country);
    void on_nextFlag_clicked();
    void invalidGuessSlot();
    void backToHomeSlot();
    void receiveFlagAnimation(QString filepath, int event);
    void on_currentGuess_textChanged(const QString &arg1);
    void shakeGuessBox();
    void openHelpWindow();
    void openGameWindow();
    void on_suggList_itemClicked(QListWidgetItem *item);

private:
    Ui::GameWindow *ui;
    GameWindowHelp gameWindowHelp;
    void hideWinScreen();
    void userGuessed();
    void clearHintsAndGuesses();
    void addSuggestions(std::vector<string> suggestions);
    int getRotationAngle(std::string direction);
    bool left;
    int shakeCount;
    QTimer shakeTimer;

signals:
    void newGuess(std::string currGuess);
    void newGame(int difficulty);
    void nextCountry();
    void userTypingAndNeedsSuggestions(string currentText);
    void backToHome();
    void resetGame();
};

#endif // GAMEWINDOW_H
