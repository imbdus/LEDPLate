#include "form_count.h"
#include "ui_form_count.h"

Form_count::Form_count(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_count)
{
    ui->setupUi(this);
}

Form_count::~Form_count()
{
    delete ui;
}
