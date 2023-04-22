#ifndef UIPHYSICS_H
#define UIPHYSICS_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QImage>

class UIPhysics : public QWidget
{
    Q_OBJECT
public:
    QImage image;
    QTimer timer;

    explicit UIPhysics(QWidget *parent = nullptr);
//    explicit UIPhysics(QString imgPath = "", QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void set();


public slots:
    void updateWorld();
    //void receivePixmap(QPixmap flag);
signals:

private:

    b2World world;
    b2Body* body;





};

#endif // UIPHYSICS_H
