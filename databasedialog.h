#ifndef DATABASEDIALOG_H
#define DATABASEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class databasedialog;
}

class databasedialog : public QDialog
{
    Q_OBJECT

public:
    explicit databasedialog(QWidget *parent = nullptr);
    ~databasedialog();

    QString db_name;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::databasedialog *ui;
};

#endif // DATABASEDIALOG_H
