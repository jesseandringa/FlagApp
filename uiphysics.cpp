#include "uiphysics.h"
#include <QPainter>
#include <QDebug>


/////constructor.
UIPhysics::UIPhysics(QWidget *parent) : QWidget(parent),
    image(":/flags/FlagImages/argentina.jpg"),
    timer(this),
    count(10),
    event(1),
    turnDir(1),
    turnAngle(0),
    world(b2Vec2(0.0f, 50.0f))
{
    connect(&timer, &QTimer::timeout, this, &UIPhysics::updateWorld);
    set();
}

void UIPhysics::set(){

    turnDir = 1;
    turnAngle = 0;

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(10.0f, 33.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);

    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 1.0;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

}

void UIPhysics::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);
    b2Vec2 position = body->GetPosition();
//    float angle = body->GetAngle();

    //use this print statement to check out how the meters look
    //printf("%4.2f %4.2f %4.2f\n", position.x, position.y);
    if(event == 1){
        painter.drawImage((int)(position.x - count), (int)(position.y*20), image);
    } else if(event == 2) {
        painter.translate(this->width()/2, this->height()/4);
        painter.rotate(turnAngle);
        painter.translate(-this->width()/2, -this->height()/4);
        painter.drawImage(position.x, position.y, image);
        painter.resetTransform();
        if(turnAngle == 45){
            turnDir = -1;
        } else if(turnAngle == -45){
            turnDir = 1;
        }
        turnAngle += 2.5 * turnDir;
    }

//    qDebug() << image;
    painter.end();
    count++;
   }


void UIPhysics::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    if(event == 1){
        world.Step(1.0/60.0, 6, 2);
    }
    count++;
    update();
}
