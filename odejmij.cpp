#include "odejmij.h"
#include "ui_odejmij.h"
#include <QKeyEvent>

odejmij::odejmij(QString produkt,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::odejmij)
{
    ui->setupUi(this);
    setWindowTitle(tr("Odejmuje"));
    QValidator *validator = new QIntValidator(1, 2147483646, this);
    ui->lineEdit->setValidator(validator);
    ui->label->setText(produkt);
    setWindowFlags(Qt::WindowTitleHint);
}

odejmij::~odejmij()
{
    delete ui;
}

void odejmij::on_anuluj_clicked()
{
    everything=0;
    ilosc=0;
    close();
}

void odejmij::on_zastosuj_clicked()
{
    ilosc = ui->lineEdit->text().toInt();
    everything=ui->checkBox->isChecked();
    close();
}

void odejmij::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Escape)
        on_anuluj_clicked();
}
