#include "warehouse.h"
#include "connectDB.h"
#include "newproduct.h"
#include "adding.h"
#include "collecting.h"
#include "setlanguage.h"
#include <QApplication>
#include <qobject.h>
#include <QItemSelectionModel>
#include <QSettings>
#include <QShortcut>
#include <QtWidgets>
#include <QDateTime>

#include "databasedialog.h"

connectDB CDB;
QSqlTableModel model;
QModelIndexList indexes;
QTranslator translator;
QLabel *label;
QTableView *view;
QModelIndex index;
QLabel *dates_in;
QLabel *dates_out;
QItemSelectionModel *selected;
QModelIndex *m_in;
QLineEdit *searchWord;
QString d1,d2,d3,d4,d5,d6;
QSettings settings("MySoft", "baza");
char i=0;
int inr=0;
int k=0;
int id;
char lan=0;

//TODO add edit button or sth, so not only number of products is modifiable

warehouse::warehouse(const QString &tableName, QWidget *parent) : QWidget(parent)
{
    databasedialog DB_name;
    DB_name.exec();


    CDB.set_db_name(DB_name.db_name);
    model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(2, Qt::Horizontal, tr("quantiny"));
    model->setHeaderData(3, Qt::Horizontal, tr("name"));
    model->setHeaderData(4, Qt::Horizontal, tr("group1"));
    model->setHeaderData(5, Qt::Horizontal, tr("group2"));
    model->setHeaderData(6, Qt::Horizontal, tr("place"));
    model->setHeaderData(7, Qt::Horizontal, tr("condition"));
    view = new QTableView;
    view->setModel(model);
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
    view->setColumnWidth(7, settings.value("view/c7",view->width()/5).toInt());
    view->setColumnWidth(6, settings.value("view/c6",view->width()/4).toInt());
    view->setColumnWidth(5, settings.value("view/c5",view->width()/3).toInt());
    view->setColumnWidth(4, settings.value("view/c4",view->width()/3).toInt());
    view->setColumnWidth(3, settings.value("view/c3",view->width()/2).toInt());
    view->setColumnWidth(2, settings.value("view/c2",view->width()/5).toInt());
    view->setColumnWidth(1, settings.value("view/c1",view->width()/6).toInt());



    QHeaderView *headerview = view->horizontalHeader();
    QItemSelectionModel *select = view->selectionModel();

    QPushButton *add_new = new QPushButton(tr("  add new  "), this);
    QPushButton *add = new QPushButton(tr("  add  "), this);
    QPushButton *minus = new QPushButton(tr("  minus  "), this);//remove one piece of item only
    QPushButton *collect = new QPushButton(tr("  collect  "), this);//remove more
    QPushButton *searchButton = new QPushButton(tr("  search  "), this);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(add_new, QDialogButtonBox::ActionRole);
    buttonBox->addButton(add, QDialogButtonBox::ActionRole);
    buttonBox->addButton(minus, QDialogButtonBox::ActionRole);
    buttonBox->addButton(collect, QDialogButtonBox::ActionRole);

    QShortcut *shortcutN = new QShortcut(QKeySequence("N"),this);
    QShortcut *shortcutA = new QShortcut(QKeySequence("A"),this);
    QShortcut *shortcutC = new QShortcut(QKeySequence("C"),this);
    QShortcut *shortcutM = new QShortcut(QKeySequence("M"),this);
    QShortcut *shortcutReturn = new QShortcut(QKeySequence(Qt::Key_Return),this);//Enter button
    QShortcut *shortcutEnter = new QShortcut(QKeySequence(Qt::Key_Enter),this);
    QShortcut *shortcutEsc = new QShortcut(QKeySequence(Qt::Key_Escape),this);
    QShortcut *shortcutL = new QShortcut(QKeySequence(Qt::Key_L),this);
    connect(shortcutN, SIGNAL(activated()), this, SLOT(new_product()));
    connect(shortcutA, SIGNAL(activated()), this, SLOT(add()));
    connect(shortcutC, SIGNAL(activated()), this, SLOT(min_more()));
    connect(shortcutM, SIGNAL(activated()), this, SLOT(min()));
    connect(shortcutEnter, SIGNAL(activated()), this, SLOT(search()));
    connect(shortcutReturn, SIGNAL(activated()), this, SLOT(search()));
    connect(shortcutEsc, SIGNAL(activated()), this, SLOT(CancelSearch()));
    connect(shortcutL, SIGNAL(activated()), this, SLOT(slotLanguageChanged()));

    connect(add_new, SIGNAL(clicked()), this, SLOT(new_product()));
    connect(add, SIGNAL(clicked()), this, SLOT(add()));
    connect(minus, SIGNAL(clicked()), this, SLOT(min()));
    connect(collect, SIGNAL(clicked()), this, SLOT(min_more()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(view, SIGNAL(clicked(const QModelIndex&)), this, SLOT(recordSelected()));
    connect(headerview, SIGNAL(sectionResized(int,int,int)),this, SLOT(column_change()));
    connect(select, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(recordSelected()));

    searchWord = new QLineEdit;

    QHBoxLayout *top= new QHBoxLayout;
    top->addWidget(buttonBox,0,Qt::AlignLeft);
    top->addWidget(searchWord);
    top->addWidget(searchButton);

    QHBoxLayout *dates= new QHBoxLayout;
    dates_in = new QLabel;
    dates_out = new QLabel;
    dates->addWidget(dates_in);
    dates->addWidget(dates_out);

    label= new QLabel;//for informing abour result of addidg removing items from database
    label->setText(" ");
    label->setStyleSheet("QLabel { color : red; }");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(top);
    mainLayout->addWidget(view);
    mainLayout->addLayout(dates);
    mainLayout->addWidget(label);
    setLayout(mainLayout);
    showMaximized();

    translator.load(QString("baza_") + settings.value("language","en").toString());
    qApp->installTranslator(&translator);

    setWindowTitle(tr("warehouse"));
}

void warehouse::recordSelected()
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
   dates_in->setText(tr("added:")+" \n"+d1+"\n"+d2+"\n"+d3);
   dates_out->setText(tr("collected:")+" \n"+d4+"\n"+d5+"\n"+d6);
}

void warehouse::column_change()
{
    settings.setValue("view/c1",view->columnWidth(1));
    settings.setValue("view/c2",view->columnWidth(2));
    settings.setValue("view/c3",view->columnWidth(3));
    settings.setValue("view/c4",view->columnWidth(4));
    settings.setValue("view/c5",view->columnWidth(5));
    settings.setValue("view/c6",view->columnWidth(6));
    settings.setValue("view/c7",view->columnWidth(7));
}

void warehouse::new_product()
{
    newproduct *nw;
    nw = new newproduct;
    nw->exec();
    if(nw->accepted)
    {
        id = settings.value("id",48).toInt();
        id++;
        settings.setValue("id",id);
        settings.sync();

        nw->datein1=QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy");

        CDB.add_product(id,nw->PLU,nw->quantiny,nw->name,nw->group1,
                          nw->group2,nw->place,nw->condition,nw->datein1,
                          nw->datein2,nw->datein3,nw->dateout1,
                          nw->dateout2,nw->dateout3);
    upd();
    label->setText(tr("added new product!"));
    }
}

void warehouse::min()
{
    CDB.manipulate(inr,0,1,QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy"));
    upd();
    label->setText(tr("collected!"));
}

void warehouse::add()
{
    adding dod(view->model()->data(view->model()->index(k,3)).toString());
    dod.exec();
    if(dod.new_amount==0)return;
    CDB.manipulate(inr,dod.new_amount,0,QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy"));
    upd();
    label->setText(tr("added!"));
}

void warehouse::min_more()
{
    collecting od(view->model()->data(view->model()->index(k,3)).toString());
    od.exec();
    if(od.new_amount==0&&od.everything==0)return;
    if(od.everything)
        CDB.manipulate(inr,1,1,QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy"));
    else
        CDB.manipulate(inr,0,od.new_amount,QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy"));
    upd();
    label->setText(tr("collected!"));
}

void warehouse::CancelSearch()
{
    searchWord->setText("");
    search();
}

void warehouse::search()
{
    model->setFilter( QString("nazwa LIKE '%%1%' "
                              "OR PLU LIKE '%%1%' "
                              "OR quantiny LIKE '%%1%' "
                              "OR miejsce LIKE '%%1%' "
                              "OR grupa1 LIKE '%%1%' "
                              "OR grupa2 LIKE '%%1%' ").arg( searchWord->text() ));
}

void warehouse::upd()
{
    model->select();
    view->setModel(model);  
    view->setFocus();
    view->selectRow(k);
    model->submit();
}

void warehouse::slotLanguageChanged()
{
    SetLanguage *sl;
    sl= new SetLanguage;
    sl->exec();
    settings.setValue("language",sl->cl);
    label->setText(tr("language changed to ")+" "+sl->cl);
}

