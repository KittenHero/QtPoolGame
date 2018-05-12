#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <QJsonObject>
#include <memory>

#include "ball.h"
#include "table.h"

/**
 * @brief The AbstractFactory class creates instances of balls and tables
 */
class AbstractFactory
{
public:
	virtual ~AbstractFactory() {}
    /**
     * @brief makeBall creates a ball from the provided json object
     * @param config a json object containing the ball configuration
     * @return the created ball that will always be in a valid state
     * no matter the provided json
     */
	virtual std::shared_ptr<Ball> makeBall(const QJsonObject &config) const = 0;

    /**
     * @brief makeBall creates a table from the provided json object
     * @param config a json object containing the table configuration
     * @return the created table that will always be in a valid state
     * no matter the provided json
     */
	virtual std::shared_ptr<Table> makeTable(const QJsonObject &config) const = 0;
};

#endif // ABSTRACTFACTORY_H
