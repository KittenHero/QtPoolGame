#include <iostream>
#include <QJsonValue>
#include <QJsonArray>

#include "stagetwofactory.h"
#include "pocketedtable.h"
#include "matryoshkaball.h"

/**
 * @brief converts a value that is an object of the form {"x":float,"y":float} into a QVector2D with the appropriate values
 * @param v is the QJsonValue to convert
 * @return the QVector2D that is encoded in the JSon
 */
QVector2D QVector2DFromJson(const QJsonObject &v, float defaultX = 0, float defaultY = 0)
{
	return QVector2D(v["x"].toDouble(defaultX),v["y"].toDouble(defaultY));
}


std::shared_ptr<Ball> ballHelper(const QJsonObject &config, const QString& parentColour = "white") {
	auto ball = std::make_shared<MatryoshkaBall>();
	auto colour = config["colour"].toString(parentColour);
	if (config.contains("strength") && config["strength"].toDouble() <= 0) {
		std::cout << "Ball strengths must be positive; Ignoring strength" << std::endl;
	}
	ball->setStrength(config["strength"].toDouble(-1));
	ball->setColour(colour);
	ball->setVelocity(QVector2DFromJson(config["velocity"].toObject()));
	ball->setRadius(config["radius"].toDouble(10));
	ball->setPosition(QVector2DFromJson(config["position"].toObject(), ball->radius(), ball->radius()));
	ball->setMass(config["mass"].toDouble(1.0));

	for (auto inner : config["balls"].toArray())
		ball->addBall(ballHelper(inner.toObject(), colour));

	return ball;
}

std::shared_ptr<Ball> StageTwoFactory::makeBall(const QJsonObject &config) const { return ballHelper(config); }

std::shared_ptr<Table> StageTwoFactory::makeTable(const QJsonObject &config) const
{
	double width = config["size"].toObject()["x"].toDouble(600);
	double height = config["size"].toObject()["y"].toDouble(300);
	float friction = config["friction"].toDouble(0.01);
	QColor colour = QColor(config["colour"].toString("green"));

	auto table = std::make_shared<PocketedTable>(width, height, friction,colour);
	for (auto pocket : config["pockets"].toArray()) {
		auto pocketdata = pocket.toObject();
		auto position = pocketdata["position"].toObject();
		if (position["x"].type() == QJsonValue::Undefined || position["y"].type() == QJsonValue::Undefined) {
			std::cout << "Pocket position must be valid" << std::endl;
			continue;
		}
		table->addPocket(QVector2DFromJson(position), pocketdata["radius"].toDouble(15));
	}
	return table;
}
