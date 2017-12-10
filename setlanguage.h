#ifndef SETLANGUAGE_H
#define SETLANGUAGE_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class SetLanguage;
}

class SetLanguage : public QDialog
{
    Q_OBJECT

public:
    explicit SetLanguage(QWidget *parent = 0);
    ~SetLanguage();
    QString cl;

private slots:
    void on_ok_clicked();
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::SetLanguage *ui;
};

#endif // SETLANGUAGE_H
