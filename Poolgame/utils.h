#pragma once

#include <QVector2D>
#include <QMouseEvent>
#include <QDebug>

#include <limits>
#include <functional>

#include <memory>
#include <type_traits>
#include <iostream>
#include <sstream>

/* filename of the config file */
constexpr char config_path[] = "config.json";

constexpr int animFrameMS = 16;
constexpr int drawFrameMS = 16;

constexpr double DOUBLEINF = std::numeric_limits<double>::max();
constexpr double FLOATMIN = - std::numeric_limits<float>::max();
constexpr QVector2D INVALID_VECTOR2D = QVector2D(FLOATMIN, FLOATMIN);
