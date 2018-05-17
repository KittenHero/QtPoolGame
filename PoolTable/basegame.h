#include "poolgame.h"

/**
 * @brief BaseGame contains basic physics and collision detection
 */
class BaseGame : public PoolGame {
public:
  BaseGame(
	std::shared_ptr<Table> table,
	std::shared_ptr<std::vector<std::shared_ptr<Ball>>> balls
  ) : PoolGame(table, balls) {}
  ~BaseGame() {}

  /**
   * @brief draws the entire scene
   * @param painter used to paint on
   */
  void draw(QPainter &) const override;
  /**
   * @breif move the balls by one timestep
   * @param timestep
   */
  void update(float) override;
  /**
   * @brief does nothing
   * @param mouseEvent
   */
  void handleEvent(const QMouseEvent &) override {}

private:
  /**
   * @brief checks if two balls overlap
   * @param a
   * @param b
   * @return the vector from ball a to b if they overlap or the zero vector otherwise
   */
  QVector2D collisionVector(Ball &a, Ball &b) const;
  
  /**
   * @brief check if the ball is within the bounds of the table
   * @param b
   * @return the basis vector in the direction that should be reflected or zero if ball is in table 
   */
  QVector2D collisionVector(Ball &b) const;
    
  /**
   * @brief resolve bal-ball collision
   * @param b1 ball
   * @param b2 ball
   * @param collisionVector
   */
  void resolveBallCollision(Ball &, Ball &, QVector2D);
  /**
   * @brief resolve ball-table collision
   * @param b ball
   * @param collisionVector
   */
  void resolveTableCollision(Ball &, QVector2D);
};
