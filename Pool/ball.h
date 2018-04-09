#ifndef BALL_H
#define BALL_H

#include "util.h"
#include "graphic.h"
#include <QVector2D>

/**
 * @brief The Ball class is not responsible for physics calculation
 *        it exposes public radius position, velocity and mass fields
 *        so the responsible class can access them directly.
 *        You can pretend it's a struct if you like.
 */
class Ball : public Graphic
{
public:
	float radius;
	float mass;
	QVector2D position;
	QVector2D velocity;
	/**
	 * @brief Constructor for ball
	 *
	 * @param radius used for collision detection
	 * @param mass used for physics
	 * @param pos initial poisiton for the ball
	 * @param vel inital velocity for the ball
	 */
	Ball(
		float radius = 0, float mass = 0,
		const QVector2D& pos = NULL_2D,
		const QVector2D& vel = NULL_2D
	) : radius(radius), mass(mass), position(pos), velocity(vel) {}
	virtual ~Ball() {}
};

#endif // BALL_H
