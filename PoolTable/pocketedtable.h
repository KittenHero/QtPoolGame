#ifndef POCKETEDTABLE_H
#define POCKETEDTABLE_H

#include <vector>
#include <QVector2D>
#include <utility>
#include "table.h"

/**
 * @brief this type of table has pockets
 */
class PocketedTable : public Table
{
public:
	PocketedTable(float width, float height, float friction, const QColor& colour)
		: Table(width, height, friction), m_colour(colour), m_pockets() {}
	virtual ~PocketedTable() {}

	/**
	 * @brief draw the table and pockets
	 * @param painter
	 */
	void draw(QPainter& painter) const override;

	/**
	 * @brief add pockets if they're not outside the table
	 * @param centre
	 * @param radius
	 */
	void addPocket(QVector2D centre, double radius);
	std::vector<std::pair<QVector2D, double>>& pockets() { return m_pockets; }

private:
	QColor m_colour;
	std::vector<std::pair<QVector2D, double>> m_pockets;
};

#endif // POCKETEDTABLE_H
