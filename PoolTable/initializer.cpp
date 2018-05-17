#include "initializer.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "stageonefactory.h"
#include "stagetwofactory.h"
#include "gamebuilder.h"
#include "explodingballfeature.h"
#include "pocketinteractionfeature.h"

QJsonObject jsonFromFile(const std::string &configFilePath)
{
    std::ifstream configFile(configFilePath);
    if(!configFile.good())
    {
        std::cout << "could not open \"" << configFilePath <<"\"" <<std::endl;
        return QJsonObject();
    }

    std::stringstream ss;
    //associate the read buffer to the stringstream, so now string stream will use that buffer
    ss << configFile.rdbuf();
    std::string s = ss.str();
    QJsonDocument jsonDocConfig = QJsonDocument::fromJson(QByteArray::fromStdString(ss.str()));
    if(jsonDocConfig.isNull())
    {
        std::cout << configFilePath <<" is not valid Json" <<std::endl;
        return QJsonObject();
    }
    return jsonDocConfig.object();
}

std::unique_ptr<PoolGame> Initializer::createPoolgame(const std::string &configFilePath)
{

    QJsonObject config = jsonFromFile(configFilePath);

    //here the correct factory for the builder to use is selected
    //there aren't explicit subclasses of builder, rather a state variable (the factory) is used
    //to provide different behavior for different stages, additional design patterns amirite?

	// No UNORITE this isn't a state pattern
	std::shared_ptr<AbstractFactory> factory;
	if (config["stage2"].toBool(false))
		factory = std::make_shared<StageTwoFactory>();
	else
		factory = std::make_shared<StageOneFactory>();

    GameBuilder builder(factory);

	auto table = config["table"].toObject();
	builder.buildTable(table);

	if(config.contains("balls") && config["balls"].toArray().size()) {
		for (auto ball : config["balls"].toArray())
			builder.addBall(ball.toObject());
	} else {
		// if no balls then default to white ball in the centre
		auto tabledim = table["size"].toObject();
		builder.addBall(QJsonObject {
			{
				"position", QJsonObject {
					{"x", tabledim["x"].toDouble(600)/2},
					{"y", tabledim["y"].toDouble(300)/2}
				}
			}
		});
    }
	auto game = builder.getGame();

	if (stage2)
		game = std::make_unique<PocketInteractionFeature>(std::make_unique<ExplodingBallFeature>(std::move(game)));

	return game;
}
