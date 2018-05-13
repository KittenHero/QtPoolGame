#include "poolgame.h"

PoolGame::PoolGame(
	std::shared_ptr<Table> m_table, std::shared_ptr<std::vector<std::shared_ptr<Ball>>> balls
) : m_table(m_table), m_balls(balls) {

	// find the first white ball in the array
	auto it = std::find_if(
		m_balls->begin(), m_balls->end(),
		[](auto ball){ return ball->colour() == Qt::white; }
	);
	m_cueball = it != m_balls->end() ? *it : nullptr;
}

QVector2D PoolGame::collisionVector(Ball &a, Ball &b) const {

	QVector2D col = b.position() - a.position();
	if (col.length() <= a.radius() + b.radius())
		return col;
	else
		return QVector2D();
}

QVector2D PoolGame::collisionVector(Ball &b) const {

	double x = b.position().x(), y = b.position().y(), r = b.radius();
	if (x - r < 0)                 return QVector2D(-1, 0);
	if (x + r > m_table->width())  return QVector2D(1,  0);
	if (y - r < 0)                 return QVector2D(0, -1);
	if (y + r > m_table->height()) return QVector2D(0,  1);
	return QVector2D();
}
