#include "extensions.h"
#include "utils.h"

const int BallGuide::KONAMI_CODE[] = {
	Qt::Key_Up,   Qt::Key_Up,    Qt::Key_Down, Qt::Key_Down,
	Qt::Key_Left, Qt::Key_Right, Qt::Key_Left, Qt::Key_Right,
	Qt::Key_B,    Qt::Key_A
};


QVector2D lineIntersection(const QVector2D& r1,const QVector2D& v1,const QVector2D& r2,const QVector2D& v2) {
	// We used coding and algorithms to make sure the lines don't run into each other
	// if (goingToCrashIntoEachOther) dont();
	double denom = v1.x() * v2.y() - v1.y() * v2.x();
	if (denom == 0)
		return INVALID_VECTOR2D;

	// solve for intersection parameter t
	double t = v2.x()*(r1.y() - r2.y()) - v2.y()*(r1.x() - r2.x());
	t /= denom;

	return r1 + t*v1;
}

QVector2D rayIntersection(const QVector2D& origin, const QVector2D& predicted, const QVector2D& target, double collisionRadius) {
	// we used coding and algorithms to make sure the balls don't run into each other
	// if (goingToCrashIntoEachOther) dont();
	auto direct = target - origin;
	auto range = QVector2D(direct.y(), direct.x()).normalized() * collisionRadius;
	auto upper = direct + range,
		 lower = direct - range;
	auto cross = [](const QVector2D& a, const QVector2D b) -> double { return a.y() * b.x() - a.x() * b.y(); };

	// check if the velocity is between the limits
	if (cross(upper, predicted) * cross(upper, lower) < 0 || cross(lower, predicted) * cross(lower, upper) < 0)
		return INVALID_VECTOR2D;

	// use dotproduct to find angle between direct and predicted hit
	double cosA = QVector2D::dotProduct(direct.normalized(), predicted.normalized());
	double sinA = sqrt(1 - cosA*cosA);
	// use sine rule twice to get the length to the collision point
	// OMG you have no idea how long it took to get the math right
	double length = range.length() * sin(asin(direct.length() * sinA / range.length()) - acos(cosA)) / sinA;
	return predicted.normalized() * length + origin;
}

std::pair<QVector2D, QVector2D> closestIntersection(const QVector2D& origin, const QVector2D& trajectory, double collisionRadius, const std::vector<Ball*>& balls, Table* table) {

	QVector2D predicted = INVALID_VECTOR2D;
	QVector2D normal = INVALID_VECTOR2D;

	auto capturePoint = [&predicted, &normal, origin](QVector2D p) -> void {
		if (predicted.distanceToPoint(origin) <= p.distanceToPoint(origin)) return;
		predicted = p;
		normal = INVALID_VECTOR2D;
	};
	auto captureLine = [&predicted, &normal, origin](QVector2D p, QVector2D dir) -> void {
		if (predicted.distanceToPoint(origin) <= p.distanceToPoint(origin)) return;
		predicted = p;
		normal = dir;
	};
	double vx = trajectory.x(), vy = trajectory.y();
	if (vx < 0){
		captureLine(lineIntersection(origin, trajectory, QVector2D(collisionRadius,0), QVector2D(0, 1)), QVector2D(1, 0));
	} else if (vx > 0) {
		captureLine(lineIntersection(origin, trajectory, QVector2D(table->getWidth() - collisionRadius,0), QVector2D(0, 1)), QVector2D(1,0));
	}
	if (vy < 0) {
		captureLine(lineIntersection(origin, trajectory, QVector2D(0,collisionRadius), QVector2D(1, 0)), QVector2D(0,1));
	} else if (vy > 0) {
		captureLine(lineIntersection(origin, trajectory, QVector2D(0,table->getHeight() - collisionRadius), QVector2D(1, 0)), QVector2D(0,1));
	}

	for (Ball* b : balls) {
		if (dynamic_cast<CueBall*>(b)) continue;
		capturePoint(rayIntersection(origin, trajectory, b->getPosition(), b->getRadius() + collisionRadius));
	}
	if (auto* s2t = dynamic_cast<StageTwoTable*>(table)) {
		for (Pocket* p : s2t->getPockets()){
			capturePoint(rayIntersection(origin, trajectory, p->getPosition(), p->getRadius() + collisionRadius));
		}
	}
	return std::make_pair(predicted, normal);
}

void BallGuide::update(Subject *s) {
	StageThreeGame::update(s);
	if (activated < KONAMI_LEN) return;
	CueBall* cb = static_cast<CueBall*>(s);

	auto dir = cb->getMouseEnd() - cb->getMouseStart();
	if (!dir.lengthSquared()) return;
	if (!cb->isDragging()) return;

	m_points.clear();
	m_points.push_back(dir);

	QVector2D predicted = cb->getPosition();
	QVector2D normal;
	QVector2D tangent;

	for (auto i = 0; i < 3; ++i) {
		std::tie(predicted, normal) = closestIntersection(predicted, dir, cb->getRadius(), *this->m_balls, this->m_table);
		m_points.push_back(predicted);
		if (normal == INVALID_VECTOR2D) break;
		tangent.setX(-normal.y());
		tangent.setY(normal.x());
		dir = 2* QVector2D::dotProduct(dir, tangent) * tangent.normalized() - dir;
	}
}

void BallGuide::render(QPainter& p) const {
	m_table->render(p, m_screenshake);

	if (activated == KONAMI_LEN && m_points.size()) {
		auto cue_it = std::find_if(m_balls->begin(), m_balls->end(),
		   [](Ball* b) -> bool { return dynamic_cast<CueBall*>(b); }
		);
		if (cue_it != m_balls->end()) {
			p.save();
			// translate the screen bc i don't want to do math everytime i call draw lol
			p.translate(-m_screenshake.toPointF());

			CueBall* cb = static_cast<CueBall*>(*cue_it);
			double shadow = cb->getRadius();

			QColor tr(255,255,255, 80);
			QPen pen;
			pen.setColor(tr);
			pen.setWidth(shadow * 0.8);
			p.setPen(pen);
			p.setBrush(QColor(0, 0, 0, 0));
			p.drawEllipse(cb->getPosition().toPointF(), shadow*4, shadow*4);

			auto it = m_points.begin();
			auto cur = cb->getPosition() + it->normalized() * shadow*4;

			p.setBrush(tr);
			for (++it; it != m_points.end(); ++it) {
				p.drawLine(cur.toPointF(), it->toPointF());
				p.drawEllipse(it->toPointF(), shadow, shadow);
				cur = *it;
			}

			m_points.erase(std::find_if(m_points.cbegin(), m_points.cend(),
				[cb, shadow](const QVector2D& pos){ return cb->getPosition().distanceToPoint(pos) <= shadow*4; }
			), m_points.cend());

			// restore coordinates and pens/brush settings
			p.restore();
		}
	}

	for (Ball* b : *m_balls)
		b->render(p, m_screenshake);
}

void BallGuide::handleKeyEvent(QKeyEvent* e) {
	StageThreeGame::handleKeyEvent(e);
	if (e->type() != QEvent::KeyRelease) return;

	if (activated == KONAMI_LEN) return;
	if (e->key() == KONAMI_CODE[activated]) activated++;
	else activated = 0;
}
