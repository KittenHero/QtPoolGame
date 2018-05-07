#include "poolgame.h"

class GameFeature : public PoolGame {
public:
  GameFeature(PoolGame *game) : m_game(game) {}
  virtual ~GameFeature() { delete m_game; }
  
  virtual void draw(QPainter& p) { m_game->draw(p); }
  virtual void simultateTimeStep(float dtime) { m_game->simulateTimeStep(dtime); }
  virtual void handleEvent(QEvent* e) { m_game->handleEvent(e); }
  
private:
  PoolGame *m_game;
}
