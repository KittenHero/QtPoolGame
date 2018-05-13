#include "pocketedtable.h"

void PocketedTable::draw(QPainter& painter) const {
	painter.setBrush(m_colour);
	painter.drawRect(0, 0, m_width, m_height);
	painter.setClipRect(0, 0, m_width, m_height);
	painter.setBrush(Qt::black);
	for (auto pocket : m_pockets)
		painter.drawEllipse(
			pocket.first.toPointF(),
			pocket.second, pocket.second
		);
}

/**
 * @brief addPockets
 * @param centre
 * @param radius
 */
void PocketedTable::addPocket(QVector2D centre, double radius) {
	if (
		centre.x() + radius <= 0 || centre.y() + radius <= 0
		|| centre.x() - radius >= m_width
		|| centre.y() - radius >= m_height
	) return;

	m_pockets.push_back({centre, radius});
}
