#include <QApplication>

#include "dialog.h"
#include "initializer.h"
#include "poolgame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	std::unique_ptr<PoolGame> game = Initializer().createPoolgame("../PoolTable/config.json");

    //if the returned game is a nullptr the json file couldn't be found or was invalid
	if (game.get() == nullptr) return a.exec();

	Dialog w(std::move(game));
    w.show();
    w.start();

    return a.exec();
}
