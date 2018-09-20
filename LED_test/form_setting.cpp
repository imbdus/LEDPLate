#include "form_setting.h"
#include "ui_form_setting.h"

Form_Setting::Form_Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Setting)
{
    ui->setupUi(this);
    instance = myApp::getInstance();
    //label_paint = new QLabel();
    //ui->scrollArea->setWidget(label_paint);
    InitSetting();

}

Form_Setting::~Form_Setting()
{
    delete ui;
}

void Form_Setting::setComboBox()
{
    myupdate();

    ui->comboBox->clear();
    ui->comboBox->addItems(fileNameList);
}


void Form_Setting::InitSetting()
{
    ui->le_layout->setText(instance->data.Path_layoutSaveto);
    ui->le_result->setText(instance->data.Path_ResultImg);
    setComboBox();
}

void Form_Setting::myupdate()
{
    QDir fromDir = instance->data.Path_layoutSaveto;
    //mmsg(instance->data.Path_layoutSaveto)
    QStringList filters;
    filters.append("*.txt");
    filePathList.clear();
    fileNameList.clear();

    QFileInfoList fileInfoList = fromDir.entryInfoList(filters, /*QDir::AllDirs|*/QDir::Files);
    foreach (QFileInfo fileinfo, fileInfoList) {
        fileNameList.append(fileinfo.fileName());
        filePathList.append(fileinfo.absoluteFilePath());
    }
}



void Form_Setting::on_pushButton_clicked()
{
    setComboBox();
}

void Form_Setting::on_comboBox_currentIndexChanged(int index)
{
    if(!filePathList.empty() && fileNameList.size() > index && fileNameList.size() == filePathList.size() && index > 0) {

        QVector<QRect> mylayout;
        //mmsg("index " + QString::number(index))
        //mmsg("list " + QString::number(fileNameList.size()))

        QString pa = filePathList.at(index);
        if(utilize::getLayout(mylayout, pa))
        {

            //mypainter.setPen(QColor(255,0,0));
            if(mylayout.empty())
                mmsg("empty!!")
            ;
            QPixmap img(ui->label_paint->size());
            QPainter p(&img);
            img.fill(Qt::white);
            p.drawRects(mylayout);
            QPixmap fitimg = img.scaled(ui->label_paint->width(),ui->label_paint->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            //resize(img.size());
            //图像放缩到相同大小

            ui->label_paint->setPixmap(fitimg);
            p.end();
        }


        //ui->label_paint->setPixmap(img);
    }
}


void Form_Setting::on_btn_layout_clicked()
{
    QFileDialog * fdig = new QFileDialog(this);
    QString file_path = fdig->getExistingDirectory(this,"请选择保存划分的位置..","./LayoutSave");
    if(file_path.isEmpty() || false == utilize::FolderIsExist(file_path))
    {
        QMessageBox::information(NULL,"ERROR","路径为空或不存在");
    }
    else {
        instance->data.Path_layoutSaveto = file_path;
        ui->le_layout->setText(file_path);
    }

}

void Form_Setting::on_btn_result_clicked()
{
    QFileDialog * fdig = new QFileDialog(this);
    QString file_path = fdig->getExistingDirectory(this,"请选择保存检测结果的位置..","./ResultImg");
    if(file_path.isEmpty() || false == utilize::FolderIsExist(file_path))
    {
        QMessageBox::information(NULL,"ERROR","路径为空或不存在");
    }
    else {
        instance->data.Path_ResultImg = file_path;
        ui->le_result->setText(file_path);
    }
}
