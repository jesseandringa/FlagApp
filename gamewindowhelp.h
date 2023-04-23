#ifndef GAMEWINDOWHELP_H
#define GAMEWINDOWHELP_H

#include <QWidget>

namespace Ui {
class GameWindowHelp;
}

class GameWindowHelp : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindowHelp(QWidget *parent = nullptr);
    ~GameWindowHelp();

public slots:
    void backButtonClicked();

signals:
    void returnToGame();

private:
    Ui::GameWindowHelp *ui;

};

#endif // GAMEWINDOWHELP_H
