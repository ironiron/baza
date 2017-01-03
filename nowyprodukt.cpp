#include "nowyprodukt.h"
#include "ui_nowyprodukt.h"
#include <QtWidgets>
#include <QtSql>
#include <QApplication>
#include <QKeyEvent>
#include <QShortcut>

nowyprodukt::nowyprodukt( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nowyprodukt)
{
    ui->setupUi(this);
    setWindowTitle(tr("Adding new product"));
    QValidator *validator = new QIntValidator(1, 2147483646, this);
    ui->i->setValidator(validator);
    ui->p->setValidator(validator);
    setWindowFlags(Qt::WindowTitleHint);
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Return),this);//Enter button
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_d_clicked()));
}

nowyprodukt::~nowyprodukt()
{
    delete ui;
}



void nowyprodukt::on_d_clicked()
{
    accepted=TRUE;

    quantiny=ui->i->text();
    nazwa=ui->np->text();
    miejsce=ui->m->text();
    stan=ui->s->text();
    grupa1=ui->g1->text();
    grupa2=ui->g2->text();
    PLU=ui->p->text();

    ui->i->clear();
    ui->np->clear();
    ui->m->clear();
    ui->s->clear();
    ui->g1->clear();
    ui->g2->clear();
    ui->p->clear();

    close();
}

void nowyprodukt::on_a_clicked()
{
    accepted=FALSE;
    close();
}

void nowyprodukt::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Escape)
        on_a_clicked();
}
