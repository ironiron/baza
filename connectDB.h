#ifndef CONNECTDB_H
#define CONNECTDB_H
#include <QMessageBox>
#include <QSqlQuery>
#include <QString>

class connectDB : public QSqlDatabase
{

     QSqlQuery query;
     unsigned int id=1;

public:
     connectDB();
     void set_db_name(QString db_name);
     void add_product(int id, QString PLU, QString quantiny, QString name, QString group1, QString group2
                 , QString place, QString condition, QString datein1, QString datein2,
                 QString datein3, QString dateout1,
            QString dateout2, QString dateout3);
     void manipulate(int id, int add, int collect, QString date);
     bool ok;


};

#endif // CONNECTDB_H
