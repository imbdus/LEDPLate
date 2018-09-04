#include "form_layout.h"
#include "ui_form_layout.h"

Form_layout::Form_layout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_layout)
{
    ui->setupUi(this);

    initCQLabel();
}

Form_layout::~Form_layout()
{
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
            mmsg(str)
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
}
