#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <memory>

#include "poolgame.h"

/**
 * @brief The Dialog class starts up and displays a poolgame
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Dialog constructor
     * @param game is a pointer to a PoolGame, this takes ownership of that pointer
     * @param parent is the parent widget
     */
	explicit Dialog(std::unique_ptr<PoolGame> game, QWidget *parent = 0);
	~Dialog() {}
    /**
     * @brief starts the simulation
     */
    void start();
protected:
    /**
     * @brief draws the simulation
     */
    void paintEvent(QPaintEvent *);
    /**
	 * @brief mouse movements
     */
	void mouseMoveEvent(QMouseEvent *);
	/**
	 * @brief mouse presses
	 */
	void mousePressEvent(QMouseEvent *);
	/**
	 * @brief mouse release
	 */
	void mouseReleaseEvent(QMouseEvent *);
public slots:
	void updateGame();
private:
	std::unique_ptr<PoolGame> m_game;
	QTimer m_framerateTimer;
	QTimer m_timestepTimer;
};

#endif // DIALOG_H
