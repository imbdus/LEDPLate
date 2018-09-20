#include "form_product.h"
#include "ui_form_product.h"
#include <QDebug>

Form_product::Form_product(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_product)
{
    ui->setupUi(this);
    m_control = new SBaslerCameraControl(this);
    m_control->initSome();
    connect(m_control, &SBaslerCameraControl::sigCurrentImage, [=](QImage img){
        QPixmap pix = QPixmap::fromImage(img).transformed(m_matrix);
        QSize picSize(648,486);
        QPixmap scaledPixmap = pix.scaled(picSize, Qt::KeepAspectRatio);//原始分辨率是2592x1944， 此处缩小为原来的25%
        ui->image_window->setPixmap(scaledPixmap);
        ui->image_window->setFixedSize(QSize(648,486));
        ui->image_window->show();
    });
    connect(m_control, &SBaslerCameraControl::sigSizeChange, [=](QSize size){
        // 默认大小1592,1944
//        ui->label_size->setText(QString("\345\260\272\345\257\270:%0*%1").arg(QString::number(size.width())).arg(QString::number(size.height()))); // 尺寸
        ui->image_window->setFixedSize(size);
    });
    m_control->OpenCamera(m_control->cameras().first());
}

Form_product::~Form_product()
{
    m_control->deleteAll();
    delete ui;
}

void Form_product::on_pushButtonRotate_clicked()
{
    m_matrix.rotate(90);
}

void Form_product::on_pushButton_Start_clicked()
{
    if(ui->pushButton_Start->text() == "\345\274\200\345\247\213\351\207\207\351\233\206") {// 开始采集
        m_control->StartAcquire();
        ui->pushButton_Start->setText("\347\273\223\346\235\237\351\207\207\351\233\206");// 结束采集
    } else {
        m_control->StopAcquire();
        ui->pushButton_Start->setText("\345\274\200\345\247\213\351\207\207\351\233\206");// 开始采集
    }
}

void Form_product::on_comboBox_activated(int index)
{
    m_control->setFeatureTriggerModeType(index == 0);
}

void Form_product::on_pushButton_CFMode_clicked()
{
    ui->label_CFMode->setText(m_control->getFeatureTriggerModeType()?"Open":"Close");
}

void Form_product::on_pushButton_SetMode_clicked()
{
    m_control->setFeatureTriggerSourceType(ui->lineEdit_SetMode->text());
}

void Form_product::on_pushButton_GetMode_clicked()
{
    ui->label_Mode->setText(m_control->getFeatureTriggerSourceType());
}

void Form_product::on_pushButton_SetExTime_clicked()
{
    m_control->setExposureTime(ui->lineEdit_exTime->text().toDouble());
}

void Form_product::on_pushButton_getExTime_clicked()
{
    ui->label_exTime->setText(QString::number(m_control->getExposureTime()));
}

