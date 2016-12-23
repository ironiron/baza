#ifndef NOWYPRODUKT_H
#define NOWYPRODUKT_H
#include <QObject>
#include <QDialog>
#include <QtSql>
#include <QSqlQuery>
#include "magazyn.h"
#include "connectDB.h"

namespace Ui {
class nowyprodukt;
}


class nowyprodukt : public QDialog
{
    Q_OBJECT

public:
    explicit nowyprodukt(QWidget *parent = 0);
    ~nowyprodukt();

    bool accepted;

    QString PLU;
    QString quantiny;
    QString nazwa;
    QString grupa1;
    QString grupa2;
    QString miejsce;
    QString stan;
    QString datein1;
    QString datein2;
    QString datein3;
    QString dateout1;
    QString dateout2;
    QString dateout3;

private:


void keyPressEvent(QKeyEvent *e);
    Ui::nowyprodukt *ui;
private slots:
    void on_d_clicked();
    void on_a_clicked();
};

#endif // NOWYPRODUKT_H
