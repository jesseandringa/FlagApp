#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tuple>
#include "gamewindow.h"
#include "signupwindow.h"
#include "studywindow.h"


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
    void signupButtonClicked();

    void signupAttempt(std::tuple<QString, QString, QString> temp);
    void signupFailedNotAllFields();
    void signupFailedUserExists();
    void signupFailedPassWordMismatch();
    void signupSuccess();

signals:
    void startGame(int difficulty);
    void checkSignupAttempt(QString,QString,QString);
    void signupFailedNotAllFieldsFromModel();
    void signupFailedUserExistsFromModel();
    void signupFailedPasswordMismatchFromModel();

private:
    Ui::MainWindow *ui;
    GameWindow gameWindow;
    SignUpWindow signupWindow;
    StudyWindow studyWindow;
};
#endif // MAINWINDOW_H
