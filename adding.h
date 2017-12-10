#ifndef adding_H
#define adding_H

#include <QDialog>

namespace Ui {
class adding;
}

class adding : public QDialog
{
    Q_OBJECT

public:
    explicit adding(QString produkt, QWidget *parent = 0);
    ~adding();
    int new_amount;

private:
    Ui::adding *ui;
    void keyPressEvent(QKeyEvent *e);
private slots:
    void on_cancel_clicked();
    void on_add_clicked();

};

#endif // adding_H
