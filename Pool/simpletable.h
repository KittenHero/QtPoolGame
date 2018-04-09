#ifndef SIMPLETABLE_H
#define SIMPLETABLE_H

#include "table.h"

class SimpleTable : public Table
{
public:
	/**
	 * @brief SimpleTable constructor
	 *
	 * @param dimension : size of the table
	 * @param color
	 * @param friction
	 */
	SimpleTable(const QSize& dim, const QColor& color, float friction = 0.f);
	/**
	 * @brief Draws the table onto the scene
	 *
	 * @param painter for rendering the table
	 */
	void draw(QPainter& painter) const;

private:
	QColor color;
};

#endif // SIMPLETABLE_H
