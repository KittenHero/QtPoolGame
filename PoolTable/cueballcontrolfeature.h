#include "gamefeature.h"

class CueBallControlFeature : public GameFeature {
public:
    CueBallControlFeature(PoolGame *game) : GameFeature(game) {}
    ~CueBallControlFeature() {}
    
    void handleEvent(QEvent*) override;
    void draw(QPainter &) const override;

private:
    std::Pair<QVector2D, QVector2D> m_clickCoord;
};
