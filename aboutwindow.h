/// AboutWindow tells the user basic info about how to play from the mainwindow.
/// Written By: name'); DROP TABLE teams;-- ?

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>


namespace Ui {
class AboutWindow;
}

class AboutWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

public slots:
    void backButtonClicked();

signals:
    void returnToMainWindow();
private:
    Ui::AboutWindow *ui;
};

#endif // ABOUTWINDOW_H
