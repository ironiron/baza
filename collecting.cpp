#include "collecting.h"
#include "ui_collecting.h"
#include <QKeyEvent>
#include <QShortcut>
#include <QtGui/QIntValidator>

collecting::collecting(QString product,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::collecting)
{
    ui->setupUi(this);
    setWindowTitle(tr("collecting"));
    QValidator *validator = new QIntValidator(1, 2147483646, this);
    ui->lineEdit->setValidator(validator);
    ui->label->setText(product);
    setWindowFlags(Qt::WindowTitleHint);
    QShortcut *shortcut1 = new QShortcut(QKeySequence(Qt::Key_Return),this);//Enter button
    QShortcut *shortcut2 = new QShortcut(QKeySequence(Qt::Key_Enter),this);//Enter button
    connect(shortcut1, SIGNAL(activated()), this, SLOT(on_accept_clicked()));
    connect(shortcut2, SIGNAL(activated()), this, SLOT(on_accept_clicked()));
}

collecting::~collecting()
{
    delete ui;
}

void collecting::on_cancel_clicked()
{
    everything=0;
    new_amount=0;
    close();
}

void collecting::on_accept_clicked()
{
    new_amount = ui->lineEdit->text().toInt();
    everything=ui->checkBox->isChecked();
    close();
}

void collecting::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Escape)
        on_cancel_clicked();
}
