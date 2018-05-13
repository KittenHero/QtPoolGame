#ifndef POCKETINTERACTIONFEATURE_H
#define POCKETINTERACTIONFEATURE_H

#include "gamefeature.h"

class PocketInteractionFeature : public GameFeature
{
public:
	PocketInteractionFeature(std::unique_ptr<PoolGame> game)
		: GameFeature(std::move(game)), m_cuesunk(false) {}

	void draw(QPainter &) const override;
	void handleEvent(QMouseEvent* e) override;
	void update(float t) override;
private:
	bool m_cuesunk;
};

#endif // POCKETINTERACTIONFEATURE_H
