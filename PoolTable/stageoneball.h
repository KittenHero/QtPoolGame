#ifndef STAGEONEBALL_H
#define STAGEONEBALL_H

#include <QColor>
#include <QPainter>

#include "ball.h"

/**
 * @brief The StageOneBall class is a concrete version of the Ball class specific to stage one of the assignment
 */
class StageOneBall : public Ball
{
public:
	StageOneBall() {}

public:
    /**
     * @brief draw the ball
     * @param painter to use to draw the ball
     */
	void draw(QPainter &p) const override {
		p.setPen(Qt::black);
		p.setBrush(QBrush(colour()));
		p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
	}
};

#endif // STAGEONEBALL_H
