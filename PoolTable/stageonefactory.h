#ifndef STAGEONEFACTORY_H
#define STAGEONEFACTORY_H

#include <QJsonObject>

#include "abstractfactory.h"
#include "ball.h"
#include "table.h"

/**
 * @brief The StageOneFactory class creates concrete objects for stage one
 */
class StageOneFactory : public AbstractFactory
{
public:
    // AbstractFactory interface
    /**
     * @brief makes and returns a stageOneBall
     * @param config is the configuration for the ball in json format
     * @return a pointer to a valid stageOneBall
     */
	std::shared_ptr<Ball> makeBall(const QJsonObject &config) const;

    /**
     * @brief makes and returns a stageOneTable
     * @param config is the configuration for the table in json format
     * @return a pointer to a valid stageOneTable
     */
	std::shared_ptr<Table> makeTable(const QJsonObject &config) const;
};

#endif // STAGEONEFACTORY_H
