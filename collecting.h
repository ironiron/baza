#ifndef collecting_H
#define collecting_H

#include <QDialog>

namespace Ui {
class collecting;
}

class collecting : public QDialog
{
    Q_OBJECT

public:
    explicit collecting(QString produkt, QWidget *parent = 0);
    ~collecting();
    int new_amount;
    bool everything;

private:
    Ui::collecting *ui;
    void keyPressEvent(QKeyEvent *e);
private slots:
    void on_cancel_clicked();
    void on_accept_clicked();
};

#endif // collecting_H
