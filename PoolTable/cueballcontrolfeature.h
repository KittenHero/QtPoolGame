#pragma once
#include "gamefeature.h"
#include <utility>

class CueBallControlFeature : public GameFeature {
public:
	CueBallControlFeature(std::unique_ptr<PoolGame> game) : GameFeature(std::move(game)) {}
    ~CueBallControlFeature() {}
    
	void handleEvent(QMouseEvent*) override;
    void draw(QPainter &) const override;
	void update(float) override;

private:
	QVector2D m_force;
	bool m_click;
};
