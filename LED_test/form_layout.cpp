#include "form_layout.h"
#include "ui_form_layout.h"
#include <QTableWidgetItem>
#include <QDockWidget>
#include<qlayout.h>
#include <iostream>
#include <QDebug>
#include <string>
#include "sbaslercameracontrol.h"
#include <QFileDialog>
#include <QCoreApplication>
Form_layout::Form_layout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_layout)
{
    ui->setupUi(this);
    initCQLabel();

    /*----相机初始化部分----*/
    try{
    m_control = new SBaslerCameraControl(this);
    }
    catch (runtime_error &e){
        QMessageBox::critical(this,QString("警告"),QString("请检查相机电源和GigE接口!!!"));
    }
     /*----初始化结束----*/

    QCropBox = new QRect(73,102,456,790);
    QReigionBox = new QVector<QRect>;
    QReigionBox->append(QRect(80,150,50,50));
    QReigionBox->append(QRect(400,600,100,50));
    Reg = new Regression(226, 438, 480, 535, 960, 1070, 10, 0.01, "");
//    QString fileName = QFileDialog::getOpenFileName(this,tr("Load model"),".",tr(".xml"));
    //"C:\\Users\\whale\\Desktop\\LED_test\\LED_test\\model.xml"
    QString work_dir = QCoreApplication::applicationDirPath()+"/model.xml";
    QByteArray ba = work_dir.toLatin1();
    qDebug() <<work_dir;
    Reg->init(ba.data());
}
Form_layout::~Form_layout()
{
    m_control->deleteAll();//这里在程序销毁的时候有两次删除相机，一次在这，另一次在product那个类那里，
                           //这是一个待解决的bug,在Debug模式下不影响使用
    delete ui;
}

void Form_layout::initCQLabel()
{
    //delete old
    auto tmpStore = ui->label->geometry();
    ui->label->hide();
    ui->label->setParent(0);
    ui->label->deleteLater();

    //new CQLabel
    /*CQLabel **/ clabel = new CQLabel(this);
    clabel->setGeometry(tmpStore);
    clabel->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 0);}");
    //clabel->bgdimg.load("imgg.PNG");
    clabel->show();

    //connect
    //clabel ->
    connect(clabel->lie[0],SIGNAL(textChanged(QString)),ui->lineEdit,SLOT(setText(QString)));
    connect(clabel->lie[1],SIGNAL(textChanged(QString)),ui->lineEdit_2,SLOT(setText(QString)));
    connect(clabel->lie[2],SIGNAL(textChanged(QString)),ui->lineEdit_3,SLOT(setText(QString)));
    connect(clabel->lie[3],SIGNAL(textChanged(QString)),ui->lineEdit_4,SLOT(setText(QString)));

    connect(ui->lineEdit,SIGNAL(textEdited(QString)),clabel->lie[0],SLOT(setText(QString)));
    connect(ui->lineEdit_2,SIGNAL(textEdited(QString)),clabel->lie[1],SLOT(setText(QString)));
    connect(ui->lineEdit_3,SIGNAL(textEdited(QString)),clabel->lie[2],SLOT(setText(QString)));
    connect(ui->lineEdit_4,SIGNAL(textEdited(QString)),clabel->lie[3],SLOT(setText(QString)));

}

void Form_layout::on_btn_save_clicked()
{
    myApp * tmpapp = myApp::getInstance();
    QString path = tmpapp->data.Path_layoutSaveto;
    if(!utilize::FolderIsExist(path) && !utilize::Mkdir(path))
            mmsg("folder fail")
    //qDebug() << "Path_App" << '\n';
    //qDebug() << tmpapp->Path_App << '\n';
    QString filename = QFileDialog::getSaveFileName(this,"Save as",path,"*.txt");//,tr("Config Files (*.txt)"));

    qDebug() << filename << '\n';
    QFile fp(filename);
    if(!fp.open(QIODevice::WriteOnly))
    {
        mmsg("can not open" + filename);
    }
    else {
        for(int i = 0; i < clabel->m_layout.size(); i++)
        {//这里是保存layout 读layout在 utilize::getLayout()
             //前四项 属于box 后两项属于控件
            QString str = ( QString::number( clabel->m_layout[i].x()) + ' ' + \
                    QString::number( clabel->m_layout[i].y()) + ' ' +  /*box左上 y*/ \
                    QString::number( clabel->m_layout[i].width()) + ' ' +  /*box w*/ \
                    QString::number( clabel->m_layout[i].height()) + ' ' +  /*box h*/ \
                    QString::number( clabel->width()    ) + ' ' +       /*cqlabel w*/ \
                    QString::number( clabel->height()   ));              /*cqlabel h*/
            //mmsg(str)
            fp.write(str.toLocal8Bit());
            if(i != clabel->m_layout.size() -1)
                fp.write("\n");
        }
    }
    fp.close();
}

void Form_layout::on_pushButton_clicked()
{       
    clabel->m_layout.clear();    
    update();
    m_control->GrabImageOnlyOne(this->img,50);
    clabel->bgdimg = QPixmap::fromImage(this->img);
}



void Form_layout::on_CalculateBtn_clicked()
{

    QImage::Format_Indexed8;//这是Qimg的格式
    clabel->m_layout.size();//这里面存了所有的layout

    cv::Mat cvImg=cv::Mat(this->img.height(), this->img.width(), CV_8UC1, (void*)this->img.constBits(),this->img.bytesPerLine());
    cv::Mat RectImg;
    cv::Mat RectImg_channel3;
    int x = 4*clabel->m_layout[0].x(),
        y = 4*clabel->m_layout[0].y(),
        width = 4*clabel->m_layout[0].width(),
        height = 4*clabel->m_layout[0].height();
    qDebug() <<x<<y<<width<<height;
    qDebug() <<clabel->m_layout.size();
    cv::Rect CropBox= cv::Rect(x,y,width,height);

//    string basler_img_path = "C:\\Users\\whale\\Desktop\\Xu\\OK_01.tif";//测试用
//    cv::Mat img = cv::imread(basler_img_path);

    vector<cv::Rect> rects; //convert QRect to cv::Rect of ReigionBox
    for(int i = 1; i < clabel->m_layout.size(); ++i)
        {
        rects.push_back(cv::Rect(4*clabel->m_layout[i].x()-x, 4*clabel->m_layout[i].y()-y, 4*clabel->m_layout[i].width(),4*clabel->m_layout[i].height()));
    }
    vector<float> res;
    cvImg(CropBox).copyTo(RectImg);
//    cv::imshow("sad",RectImg);
    cv::cvtColor(RectImg, RectImg_channel3, CV_GRAY2BGR);
    res = Reg->predict(RectImg_channel3, rects);
    this->layout = new QVBoxLayout;
    this->dock_widget = new QDockWidget;
    this->dock_widget->setFeatures(QDockWidget::AllDockWidgetFeatures);
    this->dock_widget->setAllowedAreas(Qt::BottomDockWidgetArea);//创建DOCK
    QTableWidget* table = new QTableWidget(this); //创建一个表格
    table->setRowCount(1);    //设置行数
    table->setColumnCount(res.size()); //设置列数,每一列代表一个区域值
    QStringList column_name;
    for(int i=0; i<res.size(); i++){
        column_name<<"Region-"+QString::number(i);
        table->setItem(0,i,new QTableWidgetItem(QString::number(res[i], 'f', 2))); //设置表格内容
    }

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setHorizontalHeaderLabels(column_name); //设置行头
    this->dock_widget->setWidget(table);
    ui->LayoutForRes->addWidget(this->dock_widget);
}
