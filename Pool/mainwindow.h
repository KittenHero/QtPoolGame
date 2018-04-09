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
	 * @brief for main loop logic
	 *        controls when to update the frame
	 */
	void tick();

protected:
/**
 * @brief draws objects on the window
 *
 * @param event specifies regions to render
 */
	void paintEvent(QPaintEvent* event);

private:
	double last_tick;
	QTimer clock;
	QElapsedTimer timer;
	unique_ptr<SceneManager> scene;
};

#endif // MAINWINDOW_H
