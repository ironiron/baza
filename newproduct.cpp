#include "newproduct.h"
#include "ui_newproduct.h"
#include <QtWidgets>
#include <QApplication>
#include <QKeyEvent>
#include <QShortcut>

newproduct::newproduct( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newproduct)
{
    ui->setupUi(this);
    setWindowTitle(tr("Adding new product"));
    QValidator *validator = new QIntValidator(1, 2147483646, this);
    ui->i->setValidator(validator);
    ui->p->setValidator(validator);
    setWindowFlags(Qt::WindowTitleHint);
    QShortcut *shortcut1 = new QShortcut(QKeySequence(Qt::Key_Return),this);//Enter button
    QShortcut *shortcut2 = new QShortcut(QKeySequence(Qt::Key_Enter),this);//Enter button
    connect(shortcut1, SIGNAL(activated()), this, SLOT(on_add_clicked()));
    connect(shortcut2, SIGNAL(activated()), this, SLOT(on_add_clicked()));
}

newproduct::~newproduct()
{
    delete ui;
}



void newproduct::on_add_clicked()
{
    accepted=TRUE;

    quantiny=ui->i->text();
    name=ui->np->text();
    place=ui->m->text();
    condition=ui->s->text();
    group1=ui->g1->text();
    group2=ui->g2->text();
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

void newproduct::on_cancel_clicked()
{
    accepted=FALSE;
    close();
}

void newproduct::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Escape)
        on_cancel_clicked();
}
