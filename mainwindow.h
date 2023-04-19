#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tuple>
#include "gamewindow.h"
#include "signupwindow.h"
#include "studywindow.h"
#include "loginwindow.h"
#include "userdatahandler.h"


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
    void helpButtonClicked();
    void easyDifficultyClicked();
    void mediumDifficultyClicked();
    void hardDifficultyClicked();
    void backButtonClicked();

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

private:
    Ui::MainWindow *ui;
    GameWindow gameWindow;
    SignUpWindow signupWindow;
    LoginWindow loginwindow;
    StudyWindow studyWindow;
    UserDataHandler userdatahandler;
};
#endif // MAINWINDOW_H
