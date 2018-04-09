#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "util.h"
#include "graphic.h"
#include "table.h"
#include "ball.h"

#include <QElapsedTimer>
#include <QSize>
#include <QPaintEvent>



class SceneManager : public Graphic
{
public:
	/**
	 * @brief SceneManager Constructor
	 *
	 * @param table
	 * @param balls
	 */
	SceneManager(unique_ptr<Table> table, vector<unique_ptr<Ball>>& balls);
	~SceneManager() {}
	/**
	 * @brief take a timestep of size dtime
	 *
	 * @param dtime
	 */
	void tick(float dtime);
	/**
	 * @brief draw the current scene
	 *
	 * @param painter for rendering objects
	 */
	void draw(QPainter& painter) const;
	/**
	 * @brief retrives the size of the scene
	 *
	 * @return the size of the scene
	 */
	QSize veiwPort() const;

private:
	unique_ptr<Table> table;
	vector<unique_ptr<Ball>> balls;
};

#endif // SCENEMANAGER_H
