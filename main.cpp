#include <QApplication>
#include "warehouse.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    QSettings settings("MySoft", "baza");
    translator.load(QString("baza_") + settings.value("language","pl").toString(), a.applicationDirPath());
    a.installTranslator(&translator);

    warehouse warehouse("magazyn");
    warehouse.show();

    return a.exec();
}
