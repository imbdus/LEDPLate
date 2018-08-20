#ifndef FORM_SETTING_H
#define FORM_SETTING_H
#include "myapp.h"
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QPainter>
#include <QPaintDevice>
#include <QPaintEngine>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class Form_Setting;
}

class Form_Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Setting(QWidget *parent = 0);
    ~Form_Setting();

public slots:
    void setComboBox(/*myApp *& ins*/);

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_btn_layout_clicked();

    void on_btn_result_clicked();

private:
    Ui::Form_Setting *ui;
    myApp * instance;
    QStringList fileNameList;
    QStringList filePathList;
    //QLabel * label_paint;

private:
    void InitSetting();
    void myupdate();
};

#endif // FORM_SETTING_H
