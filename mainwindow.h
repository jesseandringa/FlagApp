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
    void signUpAttempt(std::tuple<QString, QString, QString> temp);

signals:
    void startGame(int difficulty);

private:
    Ui::MainWindow *ui;
    GameWindow gameWindow;
    SignUpWindow signupWindow;
    StudyWindow studyWindow;
};
#endif // MAINWINDOW_H
