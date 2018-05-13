#ifndef STAGETWOFACTORY_H
#define STAGETWOFACTORY_H
#include "abstractfactory.h"

class StageTwoFactory : public AbstractFactory
{
public:
	/**
	 * @brief creates a MatryshkaBall
	 * @param config is the configuration for the ball in json format
	 * @return the ball specified by the config
	 */
	std::shared_ptr<Ball> makeBall(const QJsonObject &config) const;

	/**
	 * @brief creates a PocketedTable
	 * @param config is the configuration for the table in json format
	 * @return the table specified by the config
	 */
	std::shared_ptr<Table> makeTable(const QJsonObject &config) const;
};

#endif // STAGETWOFACTORY_H
