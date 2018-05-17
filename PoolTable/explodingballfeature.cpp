#include "explodingballfeature.h"
#include "matryoshkaball.h"

#include <algorithm>
#include <math.h>

void ExplodingBallFeature::handleEvent(QMouseEvent* mouse) {
	if (mouse->button() == Qt::RightButton && mouse->type() == QEvent::MouseButtonRelease)
		MatryoshkaBall::toggleInnerVisibility();

	GameFeature::handleEvent(mouse);
}

void ExplodingBallFeature::update(float dtime) {
	std::vector<QVector2D> preVelocity;

	for (auto ball : *m_balls) {
		preVelocity.push_back(ball->velocity());
	}

	GameFeature::update(dtime);
	for (size_t i = 0; i < preVelocity.size(); ++i) {
		auto& ball = *static_cast<MatryoshkaBall*>(m_balls->at(i).get());
		if (ball.strength() < 0) continue;

		auto deltaV = ball.velocity() - preVelocity[i];
		auto energy = ball.mass() * deltaV.lengthSquared();

		if (ball.strength() > energy) continue;

		// ball strength exceeded : gets destroyed
		ball.setRadius(0);
		auto& nested = ball.nested();
		if (nested.empty())  continue;

		// calculate velocity and position for inner balls
		auto ptOfCollision(- ball.radius() * deltaV.normalized());
		auto energyFraction = energy / nested.size();
		for (auto inner : nested) {
			inner->setVelocity(
				preVelocity[i] +
				sqrt(energyFraction / inner->mass()) * (inner->position() - ptOfCollision).normalized()
			);
			inner->changePosition(ball.position());
		}
		// release the children
		m_balls->insert(m_balls->end(), nested.begin(), nested.end());
		nested.clear();
	}

	// removes all invalid ball from array
	auto isInvalid = [](auto ball){ return ball->radius() <= 0; };
	m_balls->erase(
		std::remove_if(m_balls->begin(), m_balls->end(), isInvalid),
		m_balls->end()
	);
}
