#ifndef DODAJE_H
#define DODAJE_H

#include <QDialog>

namespace Ui {
class dodaje;
}

class dodaje : public QDialog
{
    Q_OBJECT

public:
    explicit dodaje(QString produkt, QWidget *parent = 0);
    ~dodaje();
    int ilosc;

private:
    Ui::dodaje *ui;
    void keyPressEvent(QKeyEvent *e);
private slots:
    void on_anuluj_clicked();
    void on_zastosuj_clicked();

};

#endif // DODAJE_H
