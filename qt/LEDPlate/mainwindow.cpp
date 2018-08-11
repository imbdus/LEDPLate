#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitForm();
    InitMenuBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Event_popFormCount()
{
    P5_cnt = new Form_count(this);

    P5_cnt->setWindowFlags(Qt::Window); // 很关键 https://blog.csdn.net/dbzhang800/article/details/6737540
    P5_cnt->show();
}

void MainWindow::InitForm()
{

    //装载items
    ui->listWidget->clear();

    QStringList btn_name = {"生产","划分","相机","设置"};
    ui->listWidget->addItems(btn_name);
    QListWidgetItem * item_p;
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        item_p = ui->listWidget->item(i);

        item_p->setSizeHint(QSize(50,50));

        //待实现 调整items样式  https://blog.csdn.net/u011125673/article/details/51753997
            //            QTableWidgetItem *item = new QTableWidgetItem("Apple");
            //            item->setBackgroundColor(QColor(0,60,10));
            //            item->setTextColor(QColor(200,111,100));
            //            item->setFont(QFont("Helvetica"));
            //            table_widget->setItem(0,3,item);

    }

    //装载页面
    P1_setting   = new Form_Setting(this);
    P2_image     = new Form_cam(this);
    P3_layout    = new Form_layout(this);
    P4_product   = new Form_product(this);

    ui->stackedWidget->addWidget(P4_product);
    ui->stackedWidget->addWidget(P3_layout);
    ui->stackedWidget->addWidget(P2_image);
    ui->stackedWidget->addWidget(P1_setting);

    ui->stackedWidget->setCurrentWidget(P1_setting);
    P1_setting->show();

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

void MainWindow::InitApp()
{

    myApp * ins = myApp::getInstance();
    //ins->Name_config = "config.ini";
    ins->Path_App = QDir::currentPath();
    QString path = ins->Path_App + '/' + ins->Name_config;
    if(utilize::FileIsExist(path))
    {
        ins->ReadConfig(ins,path);
    }else {
        ins->AppTitle = "APP";
        ins->Path_layoutSaveto = "LayoutSave";
        ins->Path_ResultImg = "ImgResults";
        ins->ExposureTimeAbs = 0.01;
        ins->GainRaw = .0;
        ins->Width = 640;
        ins->Height = 480;
        ins->Layout_index = 0;
        ins->WriteConfig(ins);
    }
}




void MainWindow::InitMenuBar()
{

    //add menu1 Action1
    QMenu * menu1;
    menu1 = menuBar()->addMenu(tr("统计"));

    QAction * act1 = new QAction();
    act1->setText(tr("OK/NG"));
    menu1->addAction(act1);
    connect(act1,SIGNAL(triggered(bool)),this,SLOT(Event_popFormCount()));

    //add menu2 Action2
    QMenu * menu2;
    menu2 = menuBar()->addMenu(tr("其它"));

}

