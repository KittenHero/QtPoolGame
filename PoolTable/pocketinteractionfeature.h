#ifndef POCKETINTERACTIONFEATURE_H
#define POCKETINTERACTIONFEATURE_H

#include "gamefeature.h"
#include "pocketedtable.h"

/**
 * @brief adds the ability to remove balls that goes in pockets
 */
class PocketInteractionFeature : public GameFeature
{
public:
	PocketInteractionFeature(std::unique_ptr<PoolGame> game)
		: GameFeature(std::move(game)),
		m_table(std::static_pointer_cast<PocketedTable>(GameFeature::m_table)),
		m_cuesunk(false), m_cue_radius(m_cueball->radius()) {}

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
	std::shared_ptr<PocketedTable> m_table;
	bool m_cuesunk;
	double m_cue_radius;
};

#endif // POCKETINTERACTIONFEATURE_H
