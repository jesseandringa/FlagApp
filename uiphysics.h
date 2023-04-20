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
    explicit UIPhysics(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

public slots:
    void updateWorld();
signals:

private:

    b2World world;
    b2Body* body;
    QTimer timer;
    QImage image;
};

#endif // UIPHYSICS_H
