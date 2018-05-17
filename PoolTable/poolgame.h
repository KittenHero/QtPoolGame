#ifndef POOLGAME_H
#define POOLGAME_H

#include <vector>
#include <memory>
#include <algorithm>
#include <QPainter>
#include <QSize>
#include <QMouseEvent>

#include "table.h"
#include "ball.h"

/**
 * @brief The PoolGame class runs the pool game, it is in charge of the physics of the pool game as well as
 * drawing the game
 */
class PoolGame
{
public:
    /**
     * @brief PoolGame constructor
     * @param m_table a pointer to a Table object, Poolgame takes ownership of this pointer
     * @param balls a vector of pointers to balls, Poolgame takes ownership of all the contained pointers
     */

	PoolGame(std::shared_ptr<Table> m_table, std::shared_ptr<std::vector<std::shared_ptr<Ball>>> balls)
		: m_table(m_table), m_balls(balls) {
		// find the first white ball in the array
		auto it = std::find_if(
			m_balls->begin(), m_balls->end(),
			[](auto ball){ return ball->colour() == Qt::white; }
		);
		m_cueball = it != m_balls->end() ? *it : nullptr;
	}
    virtual ~PoolGame() {}

    /**
	 * @brief update the game by a timestep
	 * @param dtime the step for the game to be updated
     */
	virtual void update(float) = 0;

    /**
     * @brief draws all elements of the game, table and balls in that order
     * @param p is the painter which is used to paint the object
     */
	virtual void draw(QPainter &) const = 0;
    
    
    /**
     * @brief handles user inputs
     * @param input events
     */
	virtual void handleEvent(QMouseEvent &) = 0;

    /**
     * @brief size
     * @return the size of the game
     */
	QSize size() const {return QSize(m_table->width(), m_table->height());}

protected:
	std::shared_ptr<Table> m_table;
	std::shared_ptr<std::vector<std::shared_ptr<Ball>>> m_balls;
	std::shared_ptr<Ball> m_cueball;
};

#endif // POOLGAME_H
