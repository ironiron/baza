#include "setlanguage.h"
#include "ui_setlanguage.h"
#include <QShortcut>
#include <QKeyEvent>
#include <QMessageBox>

SetLanguage::SetLanguage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetLanguage)
{
    ui->setupUi(this);
    setWindowTitle(tr("change language"));
    QStringList lang;
    lang << "english" << "french" << "polish";
    ui->comboBox->addItems(lang);
    setWindowFlags(Qt::WindowTitleHint);
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Return),this);//Enter button
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_pushButton_clicked()));
}

SetLanguage::~SetLanguage()
{
    delete ui;
}

void SetLanguage::on_pushButton_clicked()
{
    if(ui->comboBox->currentText()=="english")
    cl="en";
    else if(ui->comboBox->currentText()=="french")
    cl="fr";
    else if(ui->comboBox->currentText()=="polish")
    cl="pl";
    QMessageBox::information(0, qApp->QObject::tr("Information"),
        qApp->QObject::tr("Please restart this app to change language"),QMessageBox::Ok);
    close();
}

void SetLanguage::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Escape)
        close();
}
