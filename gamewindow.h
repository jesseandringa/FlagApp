#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
signals:
    void setUpGame();
public slots:
    void initNewGame();

private:
    Ui::GameWindow *ui;

};

#endif // GAMEWINDOW_H
