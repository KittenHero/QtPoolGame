#pragma once
#include "poolgame.h"

/**
 * @brief GameFeature is a base class of decorator for PoolGame
 */
class GameFeature : public PoolGame {
public:
  GameFeature(std::unique_ptr<PoolGame> game) : PoolGame(*game), m_game(std::move(game)) {}
  virtual ~GameFeature() {}
  
  /**
   * @brief calls the draw method on component
   * @param painter
   */
  void draw(QPainter& p) const override { m_game->draw(p); }
  /**
   * @brief calls update on component
   * @param timestep
   */
  void update(float dtime) override { m_game->update(dtime); }
  /**
   * @brief calls event handler on component
   * @param mouseEvent
   */
  void handleEvent(QMouseEvent* e) override { m_game->handleEvent(e); }
  
private:
  std::unique_ptr<PoolGame> m_game;
};
