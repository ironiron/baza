
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
    a.setApplicationName("version-cmd");
    a.setApplicationVersion("0.9");

    magazyn magazyn("magazyn");
    magazyn.show();
   // w.show();

    return a.exec();
}
