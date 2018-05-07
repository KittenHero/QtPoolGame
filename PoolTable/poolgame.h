#ifndef POOLGAME_H
#define POOLGAME_H

#include <vector>
#include <QPainter>
#include <QSize>

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
    PoolGame(Table * m_table,std::vector<Ball*> balls, Ball* cueball)
        :m_table(m_table),m_balls(balls),m_cueball(cueball)
    {}

    /**
     * @brief simulate one timestep of the game
     * @param timeStep is the period of time that this timestep is simulating
     */
    virtual void simulateTimeStep(float timeStep);

    /**
     * @brief draws all elements of the game, table and balls in that order
     * @param p is the painter which is used to paint the object
     */
    virtaul void draw(QPainter &p) const;
    
    
    /**
     * @brief handles user inputs
     * @param input events
     */
    virtual void handleEvent(QEvent) {}

    /**
     * @brief size
     * @return the size of the game
     */
    QSize size() const {return QSize(m_table->width(),m_table->height());}

private:
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
            return QVector2D()
    }

    /**
     * @brief check if the ball is within the bounds of the table
     * @param t
     * @param b
     * @return the basis vector in the direction that should be reflected or zero if ball is in table 
     */
    QVector2D collisionVector(Table &t, Ball &b) const {
        double x = b.position().x(), y = b.position().y(), r = b.radius();
        if (x - r < 0)              return QVector2D(-1, 0);
        if (x + r > table->width()) return QVector2D(1,  0);
        if (y - r < 0)              return QVector2D(0, -1);
        if (y + r > table->height())return QVector2D(0,  1);
    }
    
    Table * m_table;
    std::vector<Ball*> m_balls;
    Ball * m_cueball;
};

#endif // POOLGAME_H
