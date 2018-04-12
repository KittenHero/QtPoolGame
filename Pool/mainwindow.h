#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QPainter>

#include "util.h"
#include "scenemanager.h"

/**
 * @brief The top level class for controlling the window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
		/**
		 * @brief Constructor
		 *
		 * @param scene a Scene for the program to render
		 * @param parent the parent Qt Object
		 */
	MainWindow(unique_ptr<SceneManager> scene, QWidget* parent = 0);
    ~MainWindow();
public slots:
	/**
	 * @brief move the scene by a small timestep
	 */
	void tick();
	/**
	 * @brief draws the next frame
	 */
	void nextFrame();

protected:
/**
 * @brief draws objects on the window
 *
 * @param event specifies regions to render
 */
	void paintEvent(QPaintEvent* event);

private:
	QTimer updater;
	QTimer ticker;
	QElapsedTimer timer;
	unique_ptr<SceneManager> scene;
};

#endif // MAINWINDOW_H
