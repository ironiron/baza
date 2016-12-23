#ifndef MAGAZYN_H
#define MAGAZYN_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QtSql>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QPushButton;
class QSqlTableModel;
QT_END_NAMESPACE

class magazyn : public QWidget
{
    Q_OBJECT
public:
    explicit magazyn(const QString &tableName, QWidget *parent = 0);


public slots:
    void dodajprodukt();
    void recordSelected();
    void min();
    void add();
    void min_more();

private:
    QPushButton *submitButton;
    QPushButton *revertButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QSqlTableModel *model;
    void upd();

};

#endif // MAGAZYN_H
