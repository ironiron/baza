#include "magazyn.h"
#include <QtWidgets>
#include <QDateTime>
#include "connectDB.h"
#include "nowyprodukt.h"
#include "dodaje.h"
#include "odejmij.h"
#include <QApplication>
#include <qobject.h>
#include <QItemSelectionModel>
#include <QtDebug>
#include <QSettings>

connectDB CDB;
QSqlTableModel model;
QModelIndexList indexes;
QLabel *label;
QTableView *view;
QModelIndex index;
QLabel *datyin;
QLabel *datyout;
QItemSelectionModel *selected;
QModelIndex *m_in;
char i=0;
int inr=0;
int k=0;
QString d1,d2,d3,d4,d5,d6;
QSettings settings("MySoft", "baza");
int id;

magazyn::magazyn(const QString &tableName, QWidget *parent) : QWidget(parent)
{

    model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(2, Qt::Horizontal, tr("ilość"));

//! [0] //! [1]
    view = new QTableView;
    view->setModel(model);
    //view->resizeColumnsToContents();
    view->hideColumn(0);
    view->hideColumn(8);
    view->hideColumn(9);
    view->hideColumn(10);
    view->hideColumn(11);
    view->hideColumn(12);
    view->hideColumn(13);
    view->setSortingEnabled(TRUE);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->selectRow(0);
    view->setColumnWidth(7, this->width()/5);
    view->setColumnWidth(6, this->width()/4);
    view->setColumnWidth(5, this->width()/3);
    view->setColumnWidth(4, this->width()/3);
    view->setColumnWidth(3, this->width()/2);
    view->setColumnWidth(2, this->width()/5);
    view->setColumnWidth(1, this->width()/6);
    QItemSelectionModel *select = view->selectionModel();



    QPushButton *dodaj = new QPushButton("  dodaj nowy  ", this);
    QPushButton *dodaj_kolejne = new QPushButton("  dodaj  ", this);
    QPushButton *minus = new QPushButton("  odbierz jeden  ", this);
    QPushButton *odbierz = new QPushButton("  odbierz wiele  ", this);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(dodaj, QDialogButtonBox::ActionRole);
    buttonBox->addButton(dodaj_kolejne, QDialogButtonBox::ActionRole);
    buttonBox->addButton(minus, QDialogButtonBox::ActionRole);
    buttonBox->addButton(odbierz, QDialogButtonBox::ActionRole);


    connect(dodaj, SIGNAL(clicked()), this, SLOT(dodajprodukt()));
    connect(dodaj_kolejne, SIGNAL(clicked()), this, SLOT(add()));
    connect(minus, SIGNAL(clicked()), this, SLOT(min()));
    connect(odbierz, SIGNAL(clicked()), this, SLOT(min_more()));
    connect(view, SIGNAL(clicked(const QModelIndex&)), this, SLOT(recordSelected()));
    connect(select, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(recordSelected()));

    QHBoxLayout *daty= new QHBoxLayout;
    datyin = new QLabel;
    datyout = new QLabel;
    daty->addWidget(datyin);
    daty->addWidget(datyout);

    label= new QLabel;
    label->setText(" ");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(buttonBox,0,Qt::AlignLeft);
    mainLayout->addWidget(view);
    mainLayout->addLayout(daty);
    mainLayout->addWidget(label);
    setLayout(mainLayout);
    showMaximized();

    setWindowTitle(tr("magazyn"));
}

void magazyn::recordSelected()
{
   index = view->currentIndex();
   QSqlRecord record;
   k = index.row();
    label->setText(tr(""));

   inr=view->model()->data(view->model()->index(k,0)).toInt();

   d1=view->model()->data(view->model()->index(k,8)).toString();
   d2=view->model()->data(view->model()->index(k,9)).toString();
   d3=view->model()->data(view->model()->index(k,10)).toString();
   d4=view->model()->data(view->model()->index(k,11)).toString();
   d5=view->model()->data(view->model()->index(k,12)).toString();
   d6=view->model()->data(view->model()->index(k,13)).toString();
   datyin->setText("nadejście \n"+d1+"\n"+d2+"\n"+d3);
   datyout->setText("odbiór \n"+d4+"\n"+d5+"\n"+d6);
}

void magazyn::dodajprodukt()
{
    nowyprodukt *nw;
    nw = new nowyprodukt;
    nw->exec();
    if(nw->accepted)
    {
        //qDebug() <<"lala:" << settings.value("id").toInt();
        id = settings.value("id",48).toInt();
        id++;
        settings.setValue("id",id);
        settings.sync();

        nw->datein1=QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy");

        CDB.dodaj_produkt(id,nw->PLU,nw->quantiny,nw->nazwa,nw->grupa1,
                          nw->grupa2,nw->miejsce,nw->stan,nw->datein1,
                          nw->datein2,nw->datein3,nw->dateout1,
                          nw->dateout2,nw->dateout3);
    upd();
    label->setText("dodano nowy produkt!");
    }
}

void magazyn::min()
{
    CDB.manipuluj(inr,0,1,QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy"));
    upd();
    label->setText("Odjęto!");
}

void magazyn::add()
{
    dodaje dod(view->model()->data(view->model()->index(k,3)).toString());
    dod.exec();
    if(dod.ilosc==0)return;
    CDB.manipuluj(inr,dod.ilosc,0,QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy"));
    upd();
    label->setText("dodano!");
}

void magazyn::min_more()
{
    odejmij od(view->model()->data(view->model()->index(k,3)).toString());
    od.exec();
    if(od.ilosc==0&&od.everything==0)return;
    if(od.everything)
        CDB.manipuluj(inr,1,1,QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy"));
    else
        CDB.manipuluj(inr,0,od.ilosc,QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy"));
    upd();
    label->setText("Odjęto!");
}

void magazyn::upd()
{
    model->select();
    view->setModel(model);  
    view->setFocus();
    view->selectRow(k);
    model->submit();
}

