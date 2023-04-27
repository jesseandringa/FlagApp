/// StatsWindow.cpp impliments displaying the users stats in a window.
/// Written By: name'); DROP TABLE teams;-- ?

#include "statswindow.h"
#include "ui_statswindow.h"

/// \brief StatsWindow::StatsWindow
/// Constructor
/// \param parent
StatsWindow::StatsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsWindow)
{
    ui->setupUi(this);
}

/// \brief StatsWindow::~StatsWindow
/// Deconstructors
StatsWindow::~StatsWindow()
{
    delete ui;
}

/// \brief StatsWindow::receiveStats
/// Takes in an array with raw stats.  Displays stats with meaning in the stats window.
/// \param stats
void StatsWindow::receiveStats(std::array<int, 6> stats)
{
    //Stat: Complete games
    double gamesPlayed = 0;
    for(int i : stats)
    {
        gamesPlayed += i;
    }
    ui->gamesPlayed->setText((QString::number((int)gamesPlayed/12)));

    //Stat: correct Guesses
    int numCorrectGuesses = 0;
    for(int i = 0; i < 5; i++)
    {
        numCorrectGuesses += stats[i];
    }
    ui->correctGuesses->setText(QString::number(numCorrectGuesses));

    //Stat: Never Got It
    ui->noCorrectGuess->setText(QString::number(stats[5]));

    //Stat: right on first guess
    ui->firstGuessRight->setText(QString::number(stats[0]));

    //Stat: every time they guessed wrong
    int totalWrongGuesses = 0;
    for(int i = 0; i < 6; i++)
    {
        totalWrongGuesses +=i*stats[i];
    }
    ui->wrongGuesses->setText(QString::number(totalWrongGuesses));
}
