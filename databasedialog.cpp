#include "databasedialog.h"
#include "ui_databasedialog.h"

databasedialog::databasedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databasedialog)
{
    ui->setupUi(this);
}

databasedialog::~databasedialog()
{
    delete ui;
}

void databasedialog::on_buttonBox_accepted()
{
    db_name=ui->lineEdit->text();
    accept();
    close();
}

