#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

#include "form_setting.h"
#include "form_cam.h"
#include "form_layout.h"
#include "form_count.h"
#include "form_product.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void Event_popFormCount();

private:

    void InitMenuBar();         //初始化菜单栏
    void InitForm();            //初始化listWidget和stackedWidget

    Ui::MainWindow *ui;

    Form_Setting * P1_setting;
    Form_cam * P2_image;
    Form_layout * P3_layout;
    Form_product * P4_product;
    Form_count * P5_cnt;


};

#endif // MAINWINDOW_H
