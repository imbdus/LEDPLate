#ifndef FORM_PRODUCT_H
#define FORM_PRODUCT_H
#include "sbaslercameracontrol.h"
#include <QWidget>

namespace Ui {
class Form_product;
}

class Form_product : public QWidget
{
    Q_OBJECT

public:
    explicit Form_product(QWidget *parent = 0);
    ~Form_product();

private slots:
    void on_pushButton_CFMode_clicked();
    void on_pushButton_SetMode_clicked();
    void on_pushButton_GetMode_clicked();
    void on_pushButton_SetExTime_clicked();
    void on_pushButton_getExTime_clicked();
    void on_Exp_spinBox_valueChanged(int value);//曝光时间
    void on_Exp_horizontalSlider_valueChanged(int value);
    void on_Gain_spinBox_valueChanged(int value);
    void on_Gain_horizontalSlider_valueChanged(int value);
    void on_Mode_comboBox_activated(int index);
    void on_pushButton_Start_clicked();

    void on_pushButton_take_photo_clicked();

private:
    Ui::Form_product *ui;

    QMatrix m_matrix;
public :
    SBaslerCameraControl* m_control = Q_NULLPTR; //相机
};

#endif // FORM_PRODUCT_H
