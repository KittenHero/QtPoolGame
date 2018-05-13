#ifndef EXPLODINGBALLFEATURE_H
#define EXPLODINGBALLFEATURE_H

#include "gamefeature.h"

class ExplodingBallFeature : public GameFeature
{
public:
	ExplodingBallFeature(std::unique_ptr<PoolGame> game) : GameFeature(std::move(game)) {}
	virtual ~ExplodingBallFeature() {}

	void update(float dtime) override;
	void handleEvent(QMouseEvent* event) override;
};

#endif // EXPLODINGBALLFEATURE_H
