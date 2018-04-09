#include "mainwindow.h"

MainWindow::MainWindow(unique_ptr<SceneManager> pool_scene, QWidget *parent)
: QMainWindow(parent), clock(this), timer(), scene(std::move(pool_scene))
{
	this->resize(this->scene->veiwPort());
	connect(&this->clock, SIGNAL(timeout()), this, SLOT(tick()));

	this->last_tick = 0;
	this->clock.start(1000 / TICK_RATE);
	this->timer.start();
}

void MainWindow::tick() {
	double dtime = timer.restart() / 1000.0;
	this->last_tick += dtime;
	this->scene->tick(dtime * 10);

	if (this->last_tick >= FRAME_TIME) {
		this->last_tick -= FRAME_TIME;
		this->update();
	}
}

void MainWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	this->scene->draw(painter);
}

MainWindow::~MainWindow()
{}
