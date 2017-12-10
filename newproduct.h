#ifndef newproduct_H
#define newproduct_H

#include <QDialog>


namespace Ui {
class newproduct;
}


class newproduct : public QDialog
{
    Q_OBJECT

public:
    explicit newproduct(QWidget *parent = 0);
    ~newproduct();

    bool accepted;

    QString PLU;
    QString quantiny;
    QString name;
    QString group1;
    QString group2;
    QString place;
    QString condition;
    QString datein1;
    QString datein2;
    QString datein3;
    QString dateout1;
    QString dateout2;
    QString dateout3;

private:


void keyPressEvent(QKeyEvent *e);
    Ui::newproduct *ui;
private slots:
    void on_cancel_clicked();
    void on_add_clicked();
};

#endif // newproduct_H
