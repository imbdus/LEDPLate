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
    connect(clabel,)

}
