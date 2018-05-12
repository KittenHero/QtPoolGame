#include "dialog.h"

#include <QPainter>
#include <QSize>

constexpr float fps = 60;
constexpr float timeStep = 0.01;

Dialog::Dialog(std::unique_ptr<PoolGame> game, QWidget *parent)
	:QDialog(parent),m_game(std::move(game)),m_framerateTimer(), m_timestepTimer()
{
    this->setMinimumSize(m_game->size());
    this->resize(m_game->size());
	connect(&m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
	connect(&m_timestepTimer,SIGNAL(timeout()),this,SLOT(updateGame()));
}

void Dialog::start()
{
	m_framerateTimer.start(1000/fps);
	m_timestepTimer.start(1000*timeStep);
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    m_game->draw(p);
}

void Dialog::mouseMoveEvent(QMouseEvent* event) {
	m_game->handleEvent(event);
	event->accept();
}
void Dialog::mousePressEvent(QMouseEvent* event) {
	m_game->handleEvent(event);
	event->accept();
}
void Dialog::mouseReleaseEvent(QMouseEvent* event) {
	m_game->handleEvent(event);
	event->accept();
}

void Dialog::updateGame()
{
	m_game->update(timeStep);
}
