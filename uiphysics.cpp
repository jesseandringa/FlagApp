///This class contains the physics world, where a ground is set to be used to bounce on, and the
///math is done to make the flag either bounce off the screen or spin and shrink.
///Created By: name'); DROP TABLE teams;-- ?
#include "uiphysics.h"
#include <QPainter>
#include <QDebug>

/////constructor.
UIPhysics::UIPhysics(QWidget *parent) : QWidget(parent),
    image(":/flags/FlagImages/argentina.jpg"),
    timer(this),
    count(1),
    event(1),
    size(1),
    turnAngle(0),
    world(b2Vec2(0.0f, 50.0f))
{
    connect(&timer, &QTimer::timeout, this, &UIPhysics::updateWorld);
    set();
}

/**
 * A helper that runs when the constructor is run.
 * This function sets the ground body definitions and creates a body for the widget.
 * @brief UIPhysics::set
 */
void UIPhysics::set(){
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(10.0f, 35.0f);

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

/**
 * Function for drawing and changing positions of the widget being animated.
 * @brief UIPhysics::paintEvent
 */
void UIPhysics::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);
    b2Vec2 position = body->GetPosition();

    //Two events, one for win case(1), one for loss case(2)
    if(event == 1){
        //Constant movement left to not interfere with position.x value becoming negative past x = 0
        painter.drawImage((int)(position.x - count), (int)(position.y*20), image);

    } else if(event == 2) {
        painter.translate(this->width()/2, this->height()/4);
        painter.rotate(turnAngle);
        painter.scale(size,size);
        painter.translate(-this->width()/2, -this->height()/4);

        //If the widget is sufficiently small, make it dissapear by not drawing it anymore.
        if (size > 0){

            painter.drawImage(position.x, position.y + 80, image);
        }

        painter.resetTransform();
        turnAngle += 2.5;
    }

    painter.end();
    count++;
}

/**
 * Updates the world and increments some parameters used in the paintEvent.
 * @brief UIPhysics::updateWorld
 */
void UIPhysics::updateWorld() {
    if(event == 1){
        world.Step(1.0/60.0, 6, 2);
    }
    count++;
    if (size > 0){
        size = size - 0.005;
    }
    update();
}
