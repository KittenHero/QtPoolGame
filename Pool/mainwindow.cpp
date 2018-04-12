#include "mainwindow.h"

MainWindow::MainWindow(unique_ptr<SceneManager> pool_scene, QWidget *parent)
: QMainWindow(parent), updater(this), ticker(this), timer(), scene(std::move(pool_scene))
{
	this->resize(this->scene->veiwPort());
	this->setStyleSheet("Background-color: #000;");
	connect(&this->updater, SIGNAL(timeout()), this, SLOT(nextFrame()));
	connect(&this->ticker, SIGNAL(timeout()), this, SLOT(tick()));

	this->updater.start(1000 / FRAME_RATE);
	this->ticker.start(1000 / TICK_RATE);
	this->timer.start();
}

void MainWindow::nextFrame() {
	this->update();
}

void MainWindow::tick() {
	double dtime = timer.restart() / 1000.0;
	this->scene->tick(dtime);
}

void MainWindow::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	this->scene->draw(painter);
}

MainWindow::~MainWindow()
{}
