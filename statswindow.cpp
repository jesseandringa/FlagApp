#include "statswindow.h"
#include "ui_statswindow.h"

StatsWindow::StatsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsWindow)
{
    ui->setupUi(this);
}

StatsWindow::~StatsWindow()
{
    delete ui;
}

/// \brief StatsWindow::receiveStats
/// Takes in an array with raw stats.  Displays stats with meaning in the stats window.
/// \param stats
void StatsWindow::receiveStats(std::array<int, 6> stats)
{
    double gamesPlayed = 0;
    for(int i : stats)
    {
        gamesPlayed += i;
    }
    ui->gamesPlayed->setText(QString::number(gamesPlayed/12));

    int gamesWon = 0;
    for(int i = 0; i < 5; i++)
    {
        gamesWon += stats[i];
    }
    ui->correctGuesses->setText(QString::number(gamesWon));

    ui->noCorrectGuess->setText(QString::number(stats[5]));

    double tempWins(gamesWon);
    double tempTotal(gamesPlayed);
    double winPercent = tempWins / tempTotal;
    ui->firstGuessRight->setText(QString::number(stats[0]));

    int totalWrongGuesses = 0;
    for(int i = 0; i < 6; i++)
    {
        totalWrongGuesses +=i*stats[i];
    }
    ui->wrongGuesses->setText(QString::number(totalWrongGuesses));
}
