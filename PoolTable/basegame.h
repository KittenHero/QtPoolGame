#include "poolgame.h"

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
  void handleEvent(QMouseEvent *) override {}

private:
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
