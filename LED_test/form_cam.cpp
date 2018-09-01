#include "form_cam.h"
#include "ui_form_cam.h"

Form_cam::Form_cam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_cam)
{
    ui->setupUi(this);
}

Form_cam::~Form_cam()
{
    delete ui;
}
