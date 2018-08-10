#include "form_layout.h"
#include "ui_form_layout.h"

Form_layout::Form_layout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_layout)
{
    ui->setupUi(this);

    initCQLabel();
}

Form_layout::~Form_layout()
{
    delete ui;
}

void Form_layout::initCQLabel()
{
    //delete old
    auto tmpStore = ui->label->geometry();
    ui->label->hide();
    ui->label->setParent(0);
    ui->label->deleteLater();

    //new CQLabel
    CQLabel * clabel = new CQLabel(this);
    clabel->setGeometry(tmpStore);
    clabel->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 0);}");
    clabel->show();

    //connect
    //clabel ->
    connect(clabel->lie[0],SIGNAL(textChanged(QString)),ui->lineEdit,SLOT(setText(QString)));
    connect(clabel->lie[1],SIGNAL(textChanged(QString)),ui->lineEdit_2,SLOT(setText(QString)));
    connect(clabel->lie[2],SIGNAL(textChanged(QString)),ui->lineEdit_3,SLOT(setText(QString)));
    connect(clabel->lie[3],SIGNAL(textChanged(QString)),ui->lineEdit_4,SLOT(setText(QString)));

    connect(ui->lineEdit,SIGNAL(textEdited(QString)),clabel->lie[0],SLOT(setText(QString)));
    connect(ui->lineEdit_2,SIGNAL(textEdited(QString)),clabel->lie[1],SLOT(setText(QString)));
    connect(ui->lineEdit_3,SIGNAL(textEdited(QString)),clabel->lie[2],SLOT(setText(QString)));
    connect(ui->lineEdit_4,SIGNAL(textEdited(QString)),clabel->lie[3],SLOT(setText(QString)));

}
