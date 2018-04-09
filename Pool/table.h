#ifndef TABLE_H
#define TABLE_H

#include "util.h"
#include "graphic.h"

class Table : public Graphic
{
public:
	QSize dimension;
	float surface_friction;

	/**
	 * @brief Constructor for Table
	 *
	 * @param dimension
	 * @param friction
	 */
	Table(const QSize& dimension, float friction = 0)
	: dimension(dimension), surface_friction(friction) {}
	virtual ~Table() {}
};

#endif // TABLE_H
