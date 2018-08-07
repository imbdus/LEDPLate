#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "formone.h"
#include "formtwo.h"
#include "formthree.h"

#include <QMenu>
#include <QAction>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitMenuBar();
    InitForm();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pop1()
{
//    QMessageBox m(this);
//    m.setWindowTitle("MyAction1");
//        m.setText("This is a messagebox for my action1.");
//        m.exec();
    FormThree * f3 = new FormThree(this);
    f3->setWindowFlags(Qt::Window); // 很关键 https://blog.csdn.net/dbzhang800/article/details/6737540
    f3->show();
}

void MainWindow::InitMenuBar()
{
//    QMenu * menu1;
//    menu1 = menuBar()->addMenu(tr("设置"));

//    QAction * act1 = new QAction();
//    act1->setText(tr("软件设置"));
//    menu1->addAction(act1);
//    connect(act1,SIGNAL(triggered(bool)),this,SLOT(pop1()));

    ui->menumenu1->setTitle(tr("统计"));


}

void MainWindow::InitForm()
{
//    QTabWidget * tabWidget = new QTabWidget(ui->centralWidget);
//    //ui->centralWidget
//    FormOne * f1 = new FormOne();
//    //ui->tabWidget->clear();
//    tabWidget->clear();
//    tabWidget->addTab(f1,"form3");
//    tabWidget->setTabPosition(QTabWidget::West);

    FormOne * one = new FormOne;
    FormTwo * two = new FormTwo;

    ui->stackedWidget->addWidget(one);
    ui->stackedWidget->addWidget(two);

    connect(this,SIGNAL(display(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    connect(this,SIGNAL(display(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));


}

void MainWindow::on_btn_shift1_clicked()
{
//    emit display(0);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_shift2_clicked()
{
//    emit display(1);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btn_shift3_clicked()
{
    //emit display(2);
}

void MainWindow::on_btn_shift4_clicked()
{
    //emit display(3);
}
