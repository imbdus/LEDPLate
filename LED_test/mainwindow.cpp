#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitApp();
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
    //connect(ui->listWidget,SIGNAL(currentRowChanged(int)),P1_setting,SLOT(on_pushButton_clicked()));

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(PagedShift(int)));


}

void MainWindow::InitApp()
{
    myApp * ins = myApp::getInstance();
    ins->data.Name_config = "config.ini";
    ins->data.Path_App = QDir::currentPath();
    ins->setting = new QSettings(ins->data.Name_config.arg(ins->data.Path_App),QSettings::IniFormat);
    QString path = ins->data.Path_App + '/' + ins->data.Name_config;
    if(utilize::FileIsExist(path))
    {
        ins->ReadConfig(ins);//,path);
    }else {
        ins->data.AppTitle = "APP";
        ins->data.Path_layoutSaveto = ins->data.Path_App + '/' + "LayoutSave";
        ins->data.Path_ResultImg = ins->data.Path_App + '/' + "ImgResults";
        ins->data.ExposureTimeAbs = 0.01;
        ins->data.GainRaw = .0;
        ins->data.Width = 640;
        ins->data.Height = 480;
        ins->data.Layout_index = 0;
        ins->WriteConfig(ins);//,path);
        mmsg(ins->data.Path_layoutSaveto)
    }
}

void MainWindow::PagedShift(int n)
{
    //mmsg(QString::number(n));
    /* 这个顺序由void MainWindow::InitForm()
        //装载页面
        顺序决定

        0   P4_product
        1   P3_layout
        2   P2_image
        3   P1_setting
    */
    QImage img;


    switch (n) {
    case 0://P4_product

        break;
    case 1://P3_layout
        //在切换到layout的时候抓取一张图 并配置为控件的背景
        P4_product->m_control->GrabImageOnlyOne(img,50);
        P3_layout->clabel->setPixmap(QPixmap::fromImage(img));
        //DEBUG
        img.save("imggg.png","PNG");

        //P3_layout->clabel->bgdimg = QPixmap::fromImage(img);
        //img.save(P3_layout->clabel->bgdimg);
        //P3_layout->clabel->bgdimg.load("imggg.png");
        //bgdimg.load("C:\\Users\\whale\\Desktop\\LED_test\\models.PNG");

    //debug painter not active 切换到
//        P3_layout->clabel->m_painter.begin(P3_layout->clabel);
//        P3_layout->clabel->m_painter.drawPixmap(0,0,P3_layout->clabel->width(),P3_layout->clabel->height(),P3_layout->clabel->bgdimg);
//        P3_layout->clabel->m_painter.end();

        //P3_layout->clabel->P3_pageShift = true;

        break;
    case 2:
        break;
    case 3:
        P1_setting->on_pushButton_clicked();
        break;

    default:
        break;
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

