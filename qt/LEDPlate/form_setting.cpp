#include "form_setting.h"
#include "ui_form_setting.h"

Form_Setting::Form_Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Setting)
{
    ui->setupUi(this);

    //

}

Form_Setting::~Form_Setting()
{
    delete ui;
}
