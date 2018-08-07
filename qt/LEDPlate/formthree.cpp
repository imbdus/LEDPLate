#include "formthree.h"
#include "ui_formthree.h"

FormThree::FormThree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormThree)
{
    ui->setupUi(this);
}

FormThree::~FormThree()
{
    delete ui;
}
