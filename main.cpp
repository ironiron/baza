
#include <QApplication>
#include "mainwindow.h"
#include "magazyn.h"
#include "connectDB.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    QTranslator translator;
    QSettings settings("MySoft", "baza");
    translator.load(QString("baza_") + settings.value("language","pl").toString(), a.applicationDirPath());
    a.installTranslator(&translator);

    magazyn magazyn("magazyn");
    magazyn.show();
   // w.show();

    return a.exec();
}
