#include "mainwindow.h"
#include "simplecreator.h"
#include <QApplication>

#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#define CONFIG_PATH "config.json"

int main(int argc, char *argv[])
{
	QFile conf_file(CONFIG_PATH);
    conf_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString content = conf_file.readAll();
    conf_file.close();

	QJsonObject config = QJsonDocument::fromJson(content.toUtf8()).object();

	QApplication a(argc, argv);
	MainWindow w(SimpleCreator().makeScene(config));
    w.show();
	return a.exec();
}
