#include "form_product.h"
#include "ui_form_product.h"

Form_product::Form_product(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_product)
{
    ui->setupUi(this);
}

Form_product::~Form_product()
{
    delete ui;
}
