#include "poolgame.h"

class BaseGame : public PoolGame {
public:
  BaseGame(Table* table, std::vector<Ball*> balls, Ball* cueball) :
  PoolGame(table, balls, cueball) {} 
  ~BaseGame() {}
  void draw(QPainter*);
  void simulatedTimeStep(float);

private:
  void resolveBallCollision(Ball &, Ball &, QVector2D)
  void resolveTableCollision(Ball &, QVector2D)
}
