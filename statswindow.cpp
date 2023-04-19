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
    int gamesPlayed = 0;
    for(int i : stats)
    {
        gamesPlayed += i;
    }
    ui->gamesPlayed->setText(QString::number(gamesPlayed));

    int gamesWon = 0;
    for(int i = 0; i < 5; i++)
    {
        gamesWon += stats[i];
    }
    ui->gamesWon->setText(QString::number(gamesWon));

    ui->gamesLost->setText(QString::number(stats[5]));

    double tempWins(gamesWon);
    double tempTotal(gamesPlayed);
    double winPercent = tempWins / tempTotal;
    ui->winPercentage->setText(QString::number(int(winPercent * 100)) + "%");

    int totalGuesses = 0;
    for(int i = 0; i < 5; i++)
    {
        int temp = stats[i];
        totalGuesses += (temp * (i+1));
    }
    totalGuesses += stats[5]*(5);
    ui->totalGuesses->setText(QString::number(totalGuesses));
}
