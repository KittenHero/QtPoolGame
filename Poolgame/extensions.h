#pragma once
#include "game.h"

class BallGuide : public StageThreeGame {
	mutable std::vector<QVector2D> m_points;
	int activated = 0;
	static constexpr int KONAMI_LEN = 10;
	static const int KONAMI_CODE[KONAMI_LEN];
public:
	BallGuide(Game* base) : StageThreeGame(base) {}
	void update(Subject* s) override;
	void render(QPainter& p) const override;
	void handleKeyEvent(QKeyEvent* e) override;
};
