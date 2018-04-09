#ifndef UTIL_H
#define UTIL_H

#include <memory>
#include <vector>
#include <QVector2D>
#include <QDebug>

#define FRAME_RATE 120.0
#define TICK_RATE 256.0

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

const QVector2D NULL_2D;
const double FRAME_TIME = 1.0 / FRAME_RATE;

#endif // UTIL_H
