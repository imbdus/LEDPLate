#include "form_layout.h"
#include "ui_form_layout.h"

Form_layout::Form_layout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_layout)
{
    ui->setupUi(this);
}

Form_layout::~Form_layout()
{
    delete ui;
}
