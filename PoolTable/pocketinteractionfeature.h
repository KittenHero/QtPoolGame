#ifndef POCKETINTERACTIONFEATURE_H
#define POCKETINTERACTIONFEATURE_H

#include "gamefeature.h"

class PocketInteractionFeature : public GameFeature
{
public:
	PocketInteractionFeature(std::unique_ptr<PoolGame> game)
		: GameFeature(std::move(game)), m_cuesunk(false) {}

	/**
	 * @brief draws the cueball when sunk
	 * @param painter
	 */
	void draw(QPainter &) const override;
	/**
	 * @brief places the ball when sunk
	 * @param mouseEvent
	 */
	void handleEvent(QMouseEvent* e) override;
	/**
	 * @brief model interactions betweeb ball and pockets
	 * @param timestep
	 */
	void update(float t) override;
private:
	bool m_cuesunk;
};

#endif // POCKETINTERACTIONFEATURE_H
