#include "cueballcontrolfeature.h"

inline double min(double a, double b) {
	return a < b ? a : b;
}

void CueBallControlFeature::handleEvent(QMouseEvent* mouse) {

	QVector2D coord = QVector2D(mouse->localPos());

	// if the ball is moving, cancel the shot
	if (m_click && m_cueball->velocity().length()) {
		m_click = false;
	// when mouse is released, shoot the cueball and clear all data
	} else if (m_click && mouse->type() == QEvent::MouseButtonRelease && mouse->button() == Qt::LeftButton) {
		m_click = false;
		m_cueball->setVelocity(m_force * 5);
	// when left clicked on cueball, grab the mouse
	} else if (mouse->button() == Qt::LeftButton && (m_cueball->position() - coord).length() < m_cueball->radius() || m_click && mouse->button() == Qt::NoButton) {
		m_click = true;
		m_force = m_cueball->position() - coord;
		m_force = m_force.normalized() * min(m_force.length(), 150);
	}
	// pass event to other features
	GameFeature::handleEvent(mouse);
}

void CueBallControlFeature::draw(QPainter& painter) const {
	GameFeature::draw(painter);
	if (m_click) {
		// draw line to indicate direction of shot
		painter.setPen(Qt::yellow);
		painter.drawLine(
			(m_cueball->position() + m_force.normalized()*m_cueball->radius()).toPointF(),
			(m_cueball->position() + m_force).toPointF()
		);
	}
}
