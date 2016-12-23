#ifndef ODEJMIJ_H
#define ODEJMIJ_H

#include <QDialog>

namespace Ui {
class odejmij;
}

class odejmij : public QDialog
{
    Q_OBJECT

public:
    explicit odejmij(QString produkt, QWidget *parent = 0);
    ~odejmij();
    int ilosc;
    bool everything;

private:
    Ui::odejmij *ui;
    void keyPressEvent(QKeyEvent *e);
private slots:
    void on_anuluj_clicked();
    void on_zastosuj_clicked();
};

#endif // ODEJMIJ_H
