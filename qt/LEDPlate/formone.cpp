#include "formone.h"
#include "ui_formone.h"

#include "formtwo.h"
#include "mainwindow.h"

FormOne::FormOne(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormOne)
{
    ui->setupUi(this);
}

FormOne::~FormOne()
{
    delete ui;
}
