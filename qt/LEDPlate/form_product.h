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
    void on_pushButtonRotate_clicked();
    void on_pushButton_Start_clicked();
    void on_comboBox_activated(int index);
    void on_pushButton_CFMode_clicked();
    void on_pushButton_SetMode_clicked();
    void on_pushButton_GetMode_clicked();
    void on_pushButton_SetExTime_clicked();
    void on_pushButton_getExTime_clicked();

private:
    Ui::Form_product *ui;
    SBaslerCameraControl* m_control = Q_NULLPTR; //相机
    QMatrix m_matrix;
};

#endif // FORM_PRODUCT_H
