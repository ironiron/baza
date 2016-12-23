#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

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
    QSqlQuery query;
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

    return true;
}

static void lalala(int PLU, int quantiny, QString nazwa, QString grupa1,QString grupa2
                   , QString miejsce, QString stan,QString datein1, QString datein2,
                   QString datein3, QString dateout1,
              QString dateout2, QString dateout3){
    QString p = QString::number(PLU);
    QString q = QString::number(quantiny);

    query.exec("insert into magazyn values('"+p+"', '"+q+"', '"+nazwa+"', "
             "'"+grupa1+"', '"+grupa2+"', '"+miejsce+"', '"+stan+"', '"+datein1+"', '"+datein2+"', "
             "'"+datein3+"', '"+dateout1+"', '"+dateout2+"', '"+dateout3+"')");
    query.exec("insert into magazyn values(172, 12, 'Holansasasdsad' ,'ha','df','dfs','dsf','null','20-11-2016','20-20-2000','null','null','null')");
}

#endif
