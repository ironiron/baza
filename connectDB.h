#ifndef CONNECTDB_H
#define CONNECTDB_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSettings>

class connectDB : public QSqlDatabase
{

     QSqlQuery query;
     unsigned int id=1;

public:
     connectDB();
     void dodaj_produkt(int id, QString PLU, QString quantiny, QString nazwa, QString grupa1, QString grupa2
                 , QString miejsce, QString stan, QString datein1, QString datein2,
                 QString datein3, QString dateout1,
            QString dateout2, QString dateout3);
     void manipuluj(int id, int dodaj, int odbierz, QString data);
     bool ok;


};

#endif // CONNECTDB_H
