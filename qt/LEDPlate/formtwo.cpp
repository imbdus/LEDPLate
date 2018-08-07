#include "formtwo.h"
#include "ui_formtwo.h"

FormTwo::FormTwo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTwo)
{
    ui->setupUi(this);
}

FormTwo::~FormTwo()
{
    delete ui;
}
