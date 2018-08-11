#include "myapp.h"

myApp* myApp::m_pInstance = new myApp;
//myApp::myApp(QObject *parent) : QObject(parent)

void myApp::ReadConfig(myApp *&ins, QString &path)
{

}

void myApp::WriteConfig(myApp *&ins)
{

}



myApp::myApp()
{    
//    QString Path_App = QDir::currentPath();
//    qDebug() << tr("Path_App") << '\n';
//    Path_layoutSaveto = "LayoutConfig";
//    if(!utilize::Mkdir(Path_App + Path_layoutSaveto))
//        qDebug() << "path fail" <<'\n';


    //readConfig()
}

//void myApp::ReadConfig()
//{
//    QString fileName = myApp::AppPath + "config.txt";
//    //如果配置文件不存在,则以初始值继续运行
//    if (!myHelper::FileIsExist(fileName)) {
//        qDebug()<<"Config File Doesn't Exist";
//        return;
//    }
//    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
//    set->beginGroup("AppConfig");
//    myApp::AlertPicPath = set->value("AlertPicPath").toString();
//    myApp::ObjectPicPath = set->value("ObjectPicPath").toString();
//    myApp::UserName = set->value("UserName").toString();
//    myApp::Password = set->value("Password").toString();
//    myApp::HostName = set->value("HostName").toString();
//    myApp::DatabaseName = set->value("DatabaseName").toString();
//    set->endGroup();
//}

//void myApp::WriteConfig()
//{
//    QString fileName = myApp::AppPath+"config.txt";
//    QSettings *set = new QSettings(fileName,QSettings::IniFormat);
//    set->beginGroup("AppConfig");
//    set->setValue("AlertPicPath", myApp::AlertPicPath);
//    set->setValue("UserName", myApp::UserName);
//    set->setValue("Password", myApp::Password);
//    set->setValue("HostName", myApp::HostName);
//    set->setValue("DatabaseName", myApp::DatabaseName);
//    set->endGroup();
//}
