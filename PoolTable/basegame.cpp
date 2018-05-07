#include "basegame.h"


void BaseGame::simulateTimeStep(float dtime)
{
    //collisions of balls with the edge of the table
    for(Ball * b: m_balls)
    {
        this->resolveTableCollision(*b, this->collisionVector(*table, *ball));
    }

    //a collision between each possible pair of balls
    for(int i = 0; i < m_balls.size();++i)
    {
        Ball &a = *m_balls[i];
        for(int j = i+1;j < m_balls.size();++j)
        {
            Ball &b = *m_balls[j];
            this->resolveBallCollision(
                a, b, this->collisionVector(a, b)
            );
        }
    }

    float scaleFactor = - dtime*m_table->friction();
    for(Ball * b: m_balls)
    {
        b->move(timeStep);
        //apply friction
        b->changeVelocity(scaleFactor * b->velocity());

        //if moving less than 5 pixels per second just stop
        if(b->velocity().length()<5)
            b->setVelocity(QVector2D());
    }
}

void BaseGame::draw(QPainter &p)
{
    m_table->draw(p);
    for(Ball * b: m_balls)
    {
        b->draw(p);
    }
}

void BaseGame::resolveBallcollision(Ball &a, Ball &b, QVector2D collisionVector)
{
    collisionVector.normalize();
    float mR = b2.mass() / b1.mass();


    //the proportion of each balls velocity along the axis of collision
    double vA = QVector2D::dotProduct(collisionVector, b1.velocity());
    double vB = QVector2D::dotProduct(collisionVector, b2.velocity());
    //the balls are moving away from each other so do nothing
    if (vA <= 0 && vB >= 0) {
      return;
    }

    //The velocity of each ball after a collision can be found by solving the quadratic equation
    //given by equating momentum and energy before and after the collision and finding the velocities
    //that satisfy this
    //-(mR+1)x^2 2*(mR*vB+vA)x -((mR-1)*vB^2+2*vA*vB)=0
    //first we find the discriminant
    double a = -(mR + 1);
    double b = 2 * (mR * vB + vA);
    double c = -((mR - 1) * vB * vB + 2 * vA * vB);
    double discriminant = sqrt(b * b - 4 * a * c);
    double root = (-b + discriminant)/(2 * a);
    //only one of the roots is the solution, the other pertains to the current velocities
    if (root - vB < 0.01) {
      root = (-b - discriminant)/(2 * a);
    }


     //The resulting changes in velocity for ball A and B
     b1.changeVelocity(mR * (vB - root) * collisionVector);
     b2.changeVelocity((root - vB) * collisionVector);
}

void PoolGame::resolveTableCollision(Ball &b, QVector2D collisionVector)
{
    // reflect on the same axis as the collision vector
    if(collisionVector.x() != 0)
        b.changeVelocity(QVector2D(-2 * b.velocity().x(), 0));

    if(collisionVector.y() != 0)
        b.changeVelocity(QVector2D(0, -2 * b.velocity().y()));
}
