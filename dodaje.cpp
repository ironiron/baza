#include "dodaje.h"
#include "ui_dodaje.h"
#include <QKeyEvent>

dodaje::dodaje(QString produkt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaje)
{
    ui->setupUi(this);
    setWindowTitle(tr("Dodaje"));
    QValidator *validator = new QIntValidator(1, 2147483646, this);
    ui->lineEdit->setValidator(validator);
    ui->label->setText(produkt);
    installEventFilter(this);
    setWindowFlags(Qt::WindowTitleHint);
}

dodaje::~dodaje()
{
    delete ui;
}

void dodaje::on_anuluj_clicked()
{
    ilosc=0;
    close();
}

void dodaje::on_zastosuj_clicked()
{
    ilosc = ui->lineEdit->text().toInt();
    close();
}

void dodaje::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Escape)
        on_anuluj_clicked();
}
