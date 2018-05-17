#include "pocketinteractionfeature.h"
#include "pocketedtable.h"

#include <QDebug>

void PocketInteractionFeature::draw(QPainter& painter) const {
	GameFeature::draw(painter);

	if (m_cuesunk) {
		painter.setPen(QColor(80,100,250, 200));
		painter.setBrush(QColor(255, 255, 255, 200));
		painter.drawEllipse(
			m_cueball->position().toPointF(),
			m_cueball->radius(), m_cueball->radius()
		);
	}
}

void PocketInteractionFeature::handleEvent(const QMouseEvent& mouse) {

	// if the ball is sunk, place the ball by clicking
	if (m_cuesunk) {
		m_cueball->setPosition(QVector2D(mouse.localPos()));
		if (mouse.type() == QEvent::MouseButtonRelease) {
			m_cuesunk = false;
			// stop the ball from moving when placed
			m_cueball->setVelocity(QVector2D());
			m_balls->push_back(m_cueball);
		}
	}

	GameFeature::handleEvent(mouse);
}

void PocketInteractionFeature::update(float dtime) {
	GameFeature::update(dtime);

	for (auto ball : *m_balls) {

		for (auto pocket : m_table->pockets()) {
			// if the bottom of the ball is in the pocket
			// it will fall towards the hole
			auto offset = pocket.first - ball->position();
			if (offset.length() <= pocket.second)
				ball->changeVelocity(dtime * 100 * (pocket.second - offset.length()) * offset.normalized());

			// if the ball is enveloped by the pocket
			// invalidate the ball
			if (offset.length() + ball->radius() <= pocket.second) {
				ball->setRadius(0);
				if (ball == m_cueball) m_cuesunk = true;
			}
		}
	}

	// remove invalid balls
	auto isInvalid = [](auto ball) { return ball->radius() <= 0; };
	m_balls->erase(std::remove_if(m_balls->begin(), m_balls->end(), isInvalid), m_balls->end());
	// restore the radius of the cueball
	m_cueball->setRadius(m_cue_radius);
}
