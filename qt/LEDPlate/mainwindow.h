#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void display(int number);


private slots:
    void pop1();

    void on_btn_shift1_clicked();

    void on_btn_shift2_clicked();

    void on_btn_shift3_clicked();

    void on_btn_shift4_clicked();

private:
    void InitMenuBar();         //初始化菜单栏
    void InitForm();            //初始化tabWidget和页面
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
