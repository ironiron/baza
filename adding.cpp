#include "adding.h"
#include "ui_adding.h"
#include <QKeyEvent>
#include <QShortcut>

adding::adding(QString produkt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adding)
{
    ui->setupUi(this);
    setWindowTitle(tr("Adding"));
    QValidator *validator = new QIntValidator(1, 2147483646, this);
    ui->lineEdit->setValidator(validator);
    ui->label->setText(produkt);
    installEventFilter(this);
    setWindowFlags(Qt::WindowTitleHint);
    QShortcut *shortcut1 = new QShortcut(QKeySequence(Qt::Key_Return),this);//Enter button
    QShortcut *shortcut2 = new QShortcut(QKeySequence(Qt::Key_Enter),this);//Enter button
    connect(shortcut1, SIGNAL(activated()), this, SLOT(on_add_clicked()));
    connect(shortcut2, SIGNAL(activated()), this, SLOT(on_add_clicked()));
}

adding::~adding()
{
    delete ui;
}

void adding::on_cancel_clicked()
{
    new_amount=0;
    close();
}

void adding::on_add_clicked()
{
    new_amount = ui->lineEdit->text().toInt();
    close();
}

void adding::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Escape)
        on_cancel_clicked();
}
