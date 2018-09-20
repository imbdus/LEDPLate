#ifndef FORM_LAYOUT_H
#define FORM_LAYOUT_H

#include <QWidget>
#include "cqlabel.h"
#include "myapp.h"
#include <QFileDialog>
#include <QFile>
#include <QDockWidget>
#include<qlayout.h>
#include <QRect>
#include <QVector>
#include "regression.h"
#include "sbaslercameracontrol.h"
#include <vector>

namespace Ui {
class Form_layout;
}

class Form_layout : public QWidget
{
    Q_OBJECT

public:
    explicit Form_layout(QWidget *parent = 0);
    ~Form_layout();
    CQLabel * clabel;
    Regression *Reg=Q_NULLPTR;// 徐航写的算法类
    SBaslerCameraControl* m_control = Q_NULLPTR; //相机
    QImage img;//保存当前图像

private slots:

    void on_btn_save_clicked();
    void on_pushButton_clicked();
    void on_CalculateBtn_clicked();

private:
    Ui::Form_layout *ui;
    QDockWidget *dock_widget; //用来显示结果的浮动窗口
    QVBoxLayout *layout;//用来放置浮动窗口的布局
    QRect *QCropBox;//在原图上裁剪的位置
    QVector<QRect> *QReigionBox;//划分的区域



    void initCQLabel();
};

#endif // FORM_LAYOUT_H
