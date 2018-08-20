#include "myapp.h"

myApp* myApp::m_pInstance = new myApp;
//myApp::myApp(QObject *parent) : QObject(parent)

void myApp::ReadConfig(myApp *&ins)//, QString &path)
{
    FILE * fp;
    fp = std::fopen("config.dat","w+");
    if(!fp)
        mmsg("can not open")
    std::fread(&ins->data,sizeof(ins->data),1,fp);
    std::fclose(fp);
}

void myApp::WriteConfig(myApp *&ins)//, QString &path)
{
    //if(true == utilize::FileIsExist(path))
    //{
//        QFile fp(path);
        FILE * fp;
        fp = std::fopen("config.dat","w+");
        if(!fp)
            mmsg("can not open")
        std::fwrite(&ins->data,sizeof(ins->data),1,fp);
        std::fclose(fp);
    //}
}


myApp::myApp()
{    
//    void MainWindow::InitApp()
//    {

//        myApp * ins = myApp::getInstance();
//        ins->data.Name_config = "config.dat";
//        ins->data.Path_App = QDir::currentPath();
//        QString path = ins->data.Path_App + '/' + ins->data.Name_config;
//        if(utilize::FileIsExist(path))
//        {
//            ins->ReadConfig(ins);//,path);
//        }else {
//            ins->data.AppTitle = "APP";
//            ins->data.Path_layoutSaveto = ins->data.Path_App + '/' + "LayoutSave";
//            ins->data.Path_ResultImg = ins->data.Path_App + '/' + "ImgResults";
//            ins->data.ExposureTimeAbs = 0.01;
//            ins->data.GainRaw = .0;
//            ins->data.Width = 640;
//            ins->data.Height = 480;
//            ins->data.Layout_index = 0;
//            ins->WriteConfig(ins);//,path);
//        }
//    }
<<<<<<< HEAD

=======
>>>>>>> lcx

}

