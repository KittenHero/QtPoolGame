#pragma once
#include "gamefeature.h"
#include <utility>

/**
 * @brief Adds the ability to shoot cueball with mouse
 */
class CueBallControlFeature : public GameFeature {
public:
	CueBallControlFeature(std::unique_ptr<PoolGame> game) : GameFeature(std::move(game)) {}
    ~CueBallControlFeature() {}
    
	/**
	 * @brief handles input for shooting cueball
	 * @param mouse
	 */
	void handleEvent(const QMouseEvent &) override;
	/**
	 * @brief draws visual cue when shooting
	 * @param painter
	 */
    void draw(QPainter &) const override;

private:
	QVector2D m_force;
	bool m_click;
};
