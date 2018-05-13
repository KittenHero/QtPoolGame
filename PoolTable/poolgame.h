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
	PoolGame(
		std::shared_ptr<Table> m_table,
		std::shared_ptr<std::vector<std::shared_ptr<Ball>>> balls
	) : m_table(m_table), m_balls(balls) {
		// find the first white ball in the array
		auto it = std::find_if(m_balls->begin(), m_balls->end(), [](auto ball){ return ball->colour() == Qt::white; });
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
	virtual void handleEvent(QMouseEvent *) = 0;

    /**
     * @brief size
     * @return the size of the game
     */
	QSize size() const {return QSize(m_table->width(), m_table->height());}

protected:
    /**
     * @brief checks if two balls overlap
     * @param a
     * @param b
     * @return the vector from ball a to b if they overlap or the zero vector otherwise
     */
    QVector2D collisionVector(Ball &a, Ball &b) const {
        
        QVector2D col = b.position() - a.position();
        if (col.length() <= a.radius() + b.radius())
            return col;
        else
			return QVector2D();
    }

    /**
     * @brief check if the ball is within the bounds of the table
     * @param b
     * @return the basis vector in the direction that should be reflected or zero if ball is in table 
     */
	QVector2D collisionVector(Ball &b) const {
        double x = b.position().x(), y = b.position().y(), r = b.radius();
		if (x - r < 0)                 return QVector2D(-1, 0);
		if (x + r > m_table->width())  return QVector2D(1,  0);
		if (y - r < 0)                 return QVector2D(0, -1);
		if (y + r > m_table->height()) return QVector2D(0,  1);
		return QVector2D();
    }
    
	std::shared_ptr<Table> m_table;
	std::shared_ptr<std::vector<std::shared_ptr<Ball>>> m_balls;
	std::shared_ptr<Ball> m_cueball;
};

#endif // POOLGAME_H
