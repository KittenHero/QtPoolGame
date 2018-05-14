#ifndef EXPLODINGBALLFEATURE_H
#define EXPLODINGBALLFEATURE_H

#include "gamefeature.h"

class ExplodingBallFeature : public GameFeature
{
public:
	ExplodingBallFeature(std::unique_ptr<PoolGame> game) : GameFeature(std::move(game)) {}
	virtual ~ExplodingBallFeature() {}

	/**
	 * @brief break balls when energy of collision exceeds strength
	 * @param timestep (ignored)
	 */
	void update(float dtime) override;
	/**
	 * @brief toggles inner ball visibility
	 * @param mouseEvent
	 */
	void handleEvent(QMouseEvent* event) override;
};

#endif // EXPLODINGBALLFEATURE_H
