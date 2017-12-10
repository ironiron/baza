#include "connectDB.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QApplication>




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

void connectDB::add_product(int id,QString PLU, QString quantiny, QString name, QString group1,
                                QString group2, QString place, QString condition,QString datein1,
                              QString datein2, QString datein3, QString dateout1,
                             QString dateout2, QString dateout3){

    QString i = QString::number(id);
    query.exec("insert into magazyn values('"+i+"','"+PLU+"', '"+quantiny+"', '"+name+"', "
             "'"+group1+"', '"+group2+"', '"+place+"', '"+condition+"', '"+datein1+"', '"+datein2+"', "
            "'"+datein3+"', '"+dateout1+"', '"+dateout2+"', '"+dateout3+"')");


}

void connectDB::manipulate(int id,int add,int collect,QString date)
{
    int ka;
    QString date1,date2,date3;
    if(add&&collect)
    {
        query.prepare("delete from magazyn where id=:ida;");
        query.bindValue(":ida",id);
        query.exec();
        return;
    }
    query.prepare("select quantiny from magazyn where id=:ida"
                  "");
    query.bindValue(":ida",id);
    query.exec();
    while (query.next()) ka=query.value(0).toInt();
    if(add)
    {
        ka=ka+add;
        query.prepare("select datein1, datein2, datein3 from magazyn where id=:ida"
                      "");
        query.bindValue(":ida",id);
        query.exec();
        while (query.next())
        {
            date1=query.value(0).toString();
            date2=query.value(1).toString();
            date3=query.value(2).toString();
        }
        date3=date2;
        date2=date1;
        date1=date;
        query.prepare("update magazyn "
                      "set quantiny=:q,datein1=:d1, datein2=:d2, datein3=:d3 "
                      "where id=:ida ;");
        query.bindValue(":q",ka);
        query.bindValue(":d1",date1);
        query.bindValue(":d2",date2);
        query.bindValue(":d3",date3);
        query.bindValue(":ida",id);
        query.exec();
    }
    else
    {
        if (collect>ka) {

            QMessageBox::critical(0, qApp->QObject::tr("Error"),
                qApp->QObject::tr("Too little \n"
                         "Try with fewer \n"), QMessageBox::Cancel);
            return;
        }
        ka=ka-collect;
        query.prepare("select dateout1, dateout2, dateout3 from magazyn where id=:ida"
                      "");
        query.bindValue(":ida",id);
        query.exec();
        while (query.next())
        {
            date1=query.value(0).toString();
            date2=query.value(1).toString();
            date3=query.value(2).toString();
        }
        date3=date2;
        date2=date1;
        date1=date;
        query.prepare("update magazyn "
                      "set quantiny=:q,dateout1=:d1, dateout2=:d2, dateout3=:d3 "
                      "where id=:ida;");
        query.bindValue(":q",ka);
        query.bindValue(":d1",date1);
        query.bindValue(":d2",date2);
        query.bindValue(":d3",date3);
        query.bindValue(":ida",id);
        query.exec();
    }

}
