#include "basegame.h"
#include <math.h>

void BaseGame::update(float dtime)
{
    //collisions of balls with the edge of the table
	for(auto b: *m_balls)
    {
		this->resolveTableCollision(*b, this->collisionVector(*b));
    }

    //a collision between each possible pair of balls
	for(auto i = m_balls->begin(); i != m_balls->end();++i)
    {
		Ball &a = **i;
		for(auto j = i+1; j != m_balls->end(); ++j)
        {
			Ball &b = **j;
            this->resolveBallCollision(
                a, b, this->collisionVector(a, b)
            );
        }
    }

	float scaleFactor = - dtime * 50 * m_table->friction();
	for(auto b: *m_balls)
    {
		b->move(dtime);
        //apply friction
        b->changeVelocity(scaleFactor * b->velocity());

        //if moving less than 5 pixels per second just stop
        if(b->velocity().length()<5)
            b->setVelocity(QVector2D());
    }
}

void BaseGame::draw(QPainter &p) const
{
    m_table->draw(p);
	for(auto b: *m_balls)
    {
        b->draw(p);
    }
}


QVector2D BaseGame::collisionVector(Ball &a, Ball &b) const {

	QVector2D col = b.position() - a.position();
	if (col.length() <= a.radius() + b.radius())
		return col;
	else
		return QVector2D();
}

QVector2D BaseGame::collisionVector(Ball &b) const {

	double x = b.position().x(), y = b.position().y(), r = b.radius();
	if (x - r < 0)                 return QVector2D(-1, 0);
	if (x + r > m_table->width())  return QVector2D(1,  0);
	if (y - r < 0)                 return QVector2D(0, -1);
	if (y + r > m_table->height()) return QVector2D(0,  1);
	return QVector2D();
}
void BaseGame::resolveBallCollision(Ball &b1, Ball &b2, QVector2D collisionVector)
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

void BaseGame::resolveTableCollision(Ball &b, QVector2D collisionVector)
{
    // ball is already reflected
    if (QVector2D::dotProduct(collisionVector, b.velocity()) < 0)
        return;
    // reflect on the same axis as the collision vector
    if(collisionVector.x() != 0)
		b.setVelocity({- b.velocity().x(), b.velocity().y()});

    if(collisionVector.y() != 0)
		b.setVelocity({b.velocity().x(), - b.velocity().y()});
}
