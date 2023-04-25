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
    void paintEvent(QPaintEvent *);
    void set();


public slots:
    void updateWorld();
    //void receivePixmap(QPixmap flag);
signals:

public:
    int count;
    int event;
private:
    int turnDir;
    float turnAngle;
    b2World world;
    b2Body* body;






};

#endif // UIPHYSICS_H
