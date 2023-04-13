#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"
#include "signupwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void playButtonClicked();
    void studyButtonClicked();
    void helpButtonClicked();
    void easyDifficultyClicked();
    void mediumDifficultyClicked();
    void hardDifficultyClicked();
    void signupButtonClicked();

signals:
    void startGame(int difficulty);

private:
    Ui::MainWindow *ui;
    GameWindow gameWindow;
    SignUpWindow signupWindow;
};
#endif // MAINWINDOW_H
