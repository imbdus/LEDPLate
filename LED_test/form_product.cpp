#include "form_product.h"
#include "ui_form_product.h"
#include <QDebug>
#include <QMessageBox>

Form_product::Form_product(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_product)
{

    ui->setupUi(this);
    m_control = new SBaslerCameraControl(this);
    try{
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
        // 默认大小2592,1944
//        ui->label_size->setText(QString("\345\260\272\345\257\270:%0*%1").arg(QString::number(size.width())).arg(QString::number(size.height()))); // 尺寸
        ui->image_window->setFixedSize(size);
    });
    m_control->OpenCamera(m_control->cameras().first());
    //显示相机的参数初始值
    m_control->setFeatureTriggerModeType(false);
    m_control->setWidth(2592);
    m_control->setHeight(1944);
    ui->Gain_spinBox->setValue(m_control->getGain());
    ui->Exp_horizontalSlider->setValue(m_control->getExposureTime());
    ui->Exp_spinBox->setValue(m_control->getExposureTime());
    }
    catch (runtime_error &e){
        ui->Exp_spinBox->setEnabled(false);
        ui->Gain_spinBox->setEnabled(false);
        ui->Exp_horizontalSlider->setEnabled(false);
        ui->Gain_horizontalSlider->setEnabled(false);
        ui->pushButton_take_photo->setEnabled(false);
        ui->pushButton_Start->setEnabled(false);
        ui->Mode_comboBox->setEnabled(false);
        QMessageBox::critical(this,QString("警告"),QString("请检查相机电源和GigE接口!!!"));
    }

}

Form_product::~Form_product()
{
    m_control->deleteAll();
    delete ui;
}



//void Form_product::on_pushButton_CFMode_clicked()
//{
//    ui->label_CFMode->setText(m_control->getFeatureTriggerModeType()?"Open":"Close");
//}

//void Form_product::on_pushButton_SetMode_clicked()
//{
//    m_control->setFeatureTriggerSourceType(ui->lineEdit_SetMode->text());
//}

//void Form_product::on_pushButton_GetMode_clicked()
//{
//    ui->label_Mode->setText(m_control->getFeatureTriggerSourceType());
//}

//void Form_product::on_pushButton_SetExTime_clicked()
//{
//    m_control->setExposureTime(ui->lineEdit_exTime->text().toDouble());
//}

//void Form_product::on_pushButton_getExTime_clicked()
//{
//    ui->label_exTime->setText(QString::number(m_control->getExposureTime()));
//}


void Form_product::on_Exp_spinBox_valueChanged(int value)
{
    ui->Exp_horizontalSlider->setValue(value);
    m_control->setExposureTime(value);
}

void Form_product::on_Exp_horizontalSlider_valueChanged(int value)
{
    ui->Exp_spinBox->setValue(value);
    m_control->setExposureTime(value);
}

void Form_product::on_Gain_spinBox_valueChanged(int value)
{
    ui->Gain_horizontalSlider->setValue(value);
    m_control->setGain(value);
}

void Form_product::on_Gain_horizontalSlider_valueChanged(int value)
{
    ui->Gain_spinBox->setValue(value);
    m_control->setGain(value);
}

void Form_product::on_Mode_comboBox_activated(int index)
{

    bool flag=(index==0);


    if (ui->pushButton_Start->text() =="\347\273\223\346\235\237\351\207\207\351\233\206") {//结束采集
        m_control->StopAcquire();
        ui->pushButton_Start->setText("\345\274\200\345\247\213\351\207\207\351\233\206");// 开始采集

    }
    ui->Exp_spinBox->setEnabled(flag);
    ui->Gain_spinBox->setEnabled(flag);
    ui->Exp_horizontalSlider->setEnabled(flag);
    ui->Gain_horizontalSlider->setEnabled(flag);
    ui->pushButton_take_photo->setEnabled(flag);
    ui->pushButton_Start->setEnabled(flag);
    if(flag){
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
        m_control->OpenCamera(m_control->cameras().first());
        m_control->setFeatureTriggerModeType(false);
    }
    else {
        m_control->deleteAll();
    }

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

void Form_product::on_pushButton_take_photo_clicked()
{

    if (ui->pushButton_Start->text() =="\347\273\223\346\235\237\351\207\207\351\233\206") {//结束采集
        m_control->StopAcquire();
        ui->pushButton_Start->setText("\345\274\200\345\247\213\351\207\207\351\233\206");// 开始采集

    }

    QImage img;

    m_control->GrabImageOnlyOne(img,50);
    QPixmap pix = QPixmap::fromImage(img).transformed(m_matrix);
    QSize picSize(648,486);
    QPixmap scaledPixmap = pix.scaled(picSize, Qt::KeepAspectRatio);
    ui->image_window->setPixmap(scaledPixmap);
    ui->image_window->setFixedSize(QSize(648,486));
    ui->image_window->show();

}
