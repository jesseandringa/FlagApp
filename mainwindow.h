/// MainWindow is the starting window for the game.  This class handles the UI for the window
/// which allows users to start game, choose a difficulty, open the study window, open the help window,
/// signup locally and login locally.
/// Written By: name'); DROP TABLE teams;-- ?

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tuple>
#include "gamewindow.h"
#include "signupwindow.h"
#include "studywindow.h"
#include "loginwindow.h"
#include "userdatahandler.h"
#include "statswindow.h"
#include "aboutwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GameModel &model,QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void playButtonClicked();
    void studyButtonClicked();
    void aboutButtonClicked();
    void easyDifficultyClicked();
    void mediumDifficultyClicked();
    void hardDifficultyClicked();
    void backHomeFromDifficultySelection();

    void signupButtonClicked();
    void signupAttemptSlot(std::tuple<QString, QString, QString> temp);
    void signupFailedNotAllFieldsSlot();
    void signupFailedUserExistsSlot();
    void signupFailedPassWordMismatchSlot();
    void signupFailedSpacesDetectedSlot();
    void signupSuccessSlot();

    void loginButtonClicked();
    void loginAttemptSlot(QString username, QString password);
    void loginFailedNotALlFieldsSlot();
    void loginFailedUserDNESlot();
    void loginSuccessfulSlot();

    void statsClicked();
    void statsReceived(array<int,6> stats);

    void countryFinishedSlot(int finishPosition);
    void difficultyFinished();
    void backHomeFromGame();
    void backHomeFromStudy();
    void backHomeFromAbout();

signals:
    void startGame(int difficulty);
    void checkSignupAttempt(QString,QString,QString);
    void signupFailedNotAllFields();
    void signupFailedUserExists();
    void signupFailedSpacesDetected();
    void signupFailedPasswordMismatch();

    void loginAttempt(QString, QString);
    void loginFailedNotAllFields();
    void loginFailedUserDNE();

    void getStats();
    void sendStats(array<int, 6> stats);

    void countryFinished(int finishPosition);

private:
    Ui::MainWindow *ui;
    GameWindow gameWindow;
    SignUpWindow signupWindow;
    LoginWindow loginwindow;
    StudyWindow studyWindow;
    UserDataHandler userdatahandler;
    StatsWindow statswindow;
    AboutWindow aboutWindow;
};
#endif // MAINWINDOW_H
