#include "matryoshkaball.h"

bool MatryoshkaBall::s_showNested = false;

float MatryoshkaBall::mass() const {
	auto effectiveMass = m_mass;
	for (auto ball : m_nested)
		effectiveMass += ball->mass();
	return effectiveMass;
}

void MatryoshkaBall::draw(QPainter& painter) const
{
	painter.setBrush(m_colour);
	painter.drawEllipse(m_position.toPointF(), m_radius, m_radius);

	if (!s_showNested) return;

	// inner ball position is relative
	// must translate coordinate to draw correctly
	painter.translate(m_position.toPointF());
	for (auto ball : m_nested) {
		ball->draw(painter);
	}
	painter.translate(- m_position.toPointF());
}

void MatryoshkaBall::addBall(std::shared_ptr<Ball> ball) {
	// inner ball must be completely contained
	if (ball->position().length() + ball->radius() > m_radius)
		return;

	// inner ball must not move
	ball->setVelocity(QVector2D());
	m_nested.push_back(ball);
}
