#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <cstdio>
//#include "connection.h"
/*
    This file defines a helper function to open a connection to an
    in-memory SQLITE database and to create a test table.

    If you want to use another database, simply modify the code
    below. All the examples in this directory use this function to
    connect to a database.
*/
 static QSqlQuery query;
//! [0]
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
//PLU
    //QSqlQuery query;
    query.exec("create table magazyn ("
               "PLU int primary key, "
               "quantiny int, "
               "nazwa varchar(30), "
               "grupa1 varchar(30), "
               "grupa2 varchar(30), "
               "miejsce varchar(20), "
               "stan varchar(20), "
               "datein1 date, "
               "datein2 date, "
               "datein3 date,"
               "dateout1 date,"
               "dateout2 date, "
               "dateout3 date)");
    query.exec("insert into magazyn values(101, 'Danny', 'Young' ,)");
    query.exec("insert into magazyn values(102, 12, 'Holand' ,'ha','df','dfs','dsf','null','20-11-2016','20-20-2000','null','null','null')");
    query.exec("insert into magazyn values(167, 000, 'Hodfg' ,'ha','ggg','gnjj','dgfddf','null')");
    query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
    query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");

    query.exec("create table items (id int primary key,"
                                             "imagefile int,"
                                             "itemtype varchar(20),"
                                             "description varchar(100))");
    query.exec("insert into items "
               "values(0, 0, 'Qt',"
               "'Qt is a full development framework with tools designed to "
               "streamline the creation of stunning applications and  "
               "amazing user interfaces for desktop, embedded and mobile "
               "platforms.')");
    query.exec("insert into items "
               "values(1, 1, 'Qt Quick',"
               "'Qt Quick is a collection of techniques designed to help "
               "developers create intuitive, modern-looking, and fluid "
               "user interfaces using a CSS & JavaScript like language.')");
    query.exec("insert into items "
               "values(2, 2, 'Qt Creator',"
               "'Qt Creator is a powerful cross-platform integrated "
               "development environment (IDE), including UI design tools "
               "and on-device debugging.')");
    query.exec("insert into items "
               "values(3, 3, 'Qt Project',"
               "'The Qt Project governs the open source development of Qt, "
               "allowing anyone wanting to contribute to join the effort "
               "through a meritocratic structure of approvers and "
               "maintainers.')");

    query.exec("create table images (itemid int, file varchar(20))");
    query.exec("insert into images values(0, 'images/qt-logo.png')");
    query.exec("insert into images values(1, 'images/qt-quick.png')");
    query.exec("insert into images values(2, 'images/qt-creator.png')");
    query.exec("insert into images values(3, 'images/qt-project.png')");

    return true;
}

static void lalala(int PLU, int quantiny, QString nazwa, QString grupa1,QString grupa2, QString stan,
              QString datein1, QString datein2, QString datein3, QString dateout1,
              QString dateout2, QString dateout3){
    QString p = QString::number(PLU);
    QString q = QString::number(quantiny);

    query.exec("insert into magazyn values('"+p+"', '"+q+"', '"+nazwa+"', '"+p+"', "
             "'"+grupa1+"', '"+grupa2+"', '"+stan+"', '"+datein1+"', '"+datein2+"', "
             "'"+datein3+"', '"+dateout1+"', '"+dateout2+"', '"+dateout3+"')");
}

