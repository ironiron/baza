#include "connectDB.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QApplication>
#include <QtDebug>
#include <qstandardpaths.h>
#include <QtWidgets>
#include <qobject.h>
#include "magazyn.h"
#include <QSettings>


connectDB::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("path");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        exit(1);
    }
QSqlQuery dada;
query=dada;

//columuns:
//id PLU quantiny name group1 group2 place state
    query.exec("create table magazyn ("
               "id int primary key,"
               "PLU int, "
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

}

void connectDB::dodaj_produkt(int id,QString PLU, QString quantiny, QString nazwa, QString grupa1,QString grupa2
                   , QString miejsce, QString stan,QString datein1, QString datein2,
                   QString datein3, QString dateout1,
              QString dateout2, QString dateout3){

    QString i = QString::number(id);
    query.exec("insert into magazyn values('"+i+"','"+PLU+"', '"+quantiny+"', '"+nazwa+"', "
             "'"+grupa1+"', '"+grupa2+"', '"+miejsce+"', '"+stan+"', '"+datein1+"', '"+datein2+"', "
            "'"+datein3+"', '"+dateout1+"', '"+dateout2+"', '"+dateout3+"')");


}

void connectDB::manipuluj(int id,int dodaj,int odbierz,QString data)
{
    int ka;
    QString data1,data2,data3;
    if(dodaj&&odbierz)
    {
        query.prepare("delete from magazyn where id=:ida;");
        query.bindValue(":ida",id);
        query.exec();
        return;
    }
    query.prepare("select quantiny from magazyn where id=:lala"
                  "");
    query.bindValue(":lala",id);
    query.exec();
    while (query.next()) ka=query.value(0).toInt();
    if(dodaj)
    {
        ka=ka+dodaj;
        query.prepare("select datein1, datein2, datein3 from magazyn where id=:ida"
                      "");
        query.bindValue(":ida",id);
        query.exec();
        while (query.next())
        {
            data1=query.value(0).toString();
            data2=query.value(1).toString();
            data3=query.value(2).toString();
        }
        data3=data2;
        data2=data1;
        data1=data;
        QString kaka = QString::number(ka);
        QString ida = QString::number(id);
        query.prepare("update magazyn "
                      "set quantiny=:q,datein1=:d1, datein2=:d2, datein3=:d3 "
                      "where id=:ida ;");
        query.bindValue(":q",kaka);
        query.bindValue(":d1",data1);
        query.bindValue(":d2",data2);
        query.bindValue(":d3",data3);
        query.bindValue(":ida",ida);
        query.exec();
    }
    else
    {
        if (odbierz>ka) {

            QMessageBox::critical(0, qApp->QObject::tr("Error"),
                qApp->QObject::tr("Too little \n"
                         "Try with fewer \n"), QMessageBox::Cancel);
            return;
        }
        ka=ka-odbierz;
        query.prepare("select dateout1, dateout2, dateout3 from magazyn where id=:ida"
                      "");
        query.bindValue(":ida",id);
        query.exec();
        while (query.next())
        {
            data1=query.value(0).toString();
            data2=query.value(1).toString();
            data3=query.value(2).toString();
        }
        data3=data2;
        data2=data1;
        data1=data;
        query.prepare("update magazyn "
                      "set quantiny=:q,dateout1=:d1, dateout2=:d2, dateout3=:d3 "
                      "where id=:ida;");
        query.bindValue(":q",ka);
        query.bindValue(":d1",data1);
        query.bindValue(":d2",data2);
        query.bindValue(":d3",data3);
        query.bindValue(":ida",id);
        query.exec();
    }

}
