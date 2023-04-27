///.h file for initalizing variables or methods in the UIPhysics .cpp file
///Created By: name'); DROP TABLE teams;-- ?
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

public:
    int count;
    int event;
    float size;

private:
    float turnAngle;
    b2World world;
    b2Body* body;
};

#endif // UIPHYSICS_H
