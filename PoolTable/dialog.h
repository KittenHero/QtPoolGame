#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>

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
    explicit Dialog(PoolGame * game, QWidget *parent = 0);
    ~Dialog();
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
     * @brief process user input
     * @return wheter the event was recognised
     */
    bool event(QEvent *);
public slots:
    void runSimulationStep();
private:
    PoolGame * m_game;
    QTimer * m_framerateTimer;
    QTimer * m_timestepTimer;
};

#endif // DIALOG_H
