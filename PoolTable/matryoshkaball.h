#ifndef MATRYOSHKABALL_H
#define MATRYOSHKABALL_H

#include "ball.h"
#include <memory>

class MatryoshkaBall : public Ball
{
public:
	MatryoshkaBall() : Ball(), m_strength(-1) {}

	void addBall(std::shared_ptr<Ball> ball);
	std::vector<std::shared_ptr<Ball>>& nested() { return m_nested; }

	/**
	 * @brief setStrength
	 * @param strength negative strength is interpreted as infinite
	 */
	void setStrength(double strength) { m_strength = strength; }
	double strength() const { return m_strength; }

	float mass() const override;

	void draw(QPainter &p) const override;
	static void toggleInnerVisibility() { s_showNested = !s_showNested; }
private:
	static bool s_showNested;
	double m_strength;
	std::vector<std::shared_ptr<Ball>> m_nested;
};

#endif // MATRYOSHKABALL_H
