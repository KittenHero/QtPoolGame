#pragma once
#include "poolgame.h"

class GameFeature : public PoolGame {
public:
  GameFeature(std::unique_ptr<PoolGame> game) : PoolGame(*game), m_game(std::move(game)) {}
  virtual ~GameFeature() {}
  
  void draw(QPainter& p) const override { m_game->draw(p); }
  void update(float dtime) override { m_game->update(dtime); }
  void handleEvent(QMouseEvent* e) override { m_game->handleEvent(e); }
  
private:
  std::unique_ptr<PoolGame> m_game;
};
