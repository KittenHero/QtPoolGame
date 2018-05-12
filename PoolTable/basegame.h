#include "poolgame.h"

class BaseGame : public PoolGame {
public:
  BaseGame(
	std::shared_ptr<Table> table,
	std::shared_ptr<std::vector<std::shared_ptr<Ball>>> balls
  ) : PoolGame(table, balls) {}
  ~BaseGame() {}

  void draw(QPainter &) const override;
  void update(float) override;
  void handleEvent(QMouseEvent *) override {}

private:
  void resolveBallCollision(Ball &, Ball &, QVector2D);
  void resolveTableCollision(Ball &, QVector2D);
};
