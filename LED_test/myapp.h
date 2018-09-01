#ifndef MYAPP_H
#define MYAPP_H
#include <QObject>
#include <QDebug>
#include <QString>
#include <QSettings>
#include "utilize.h"
#include <QCoreApplication>
#include <QMessageBox>
#include <QDir>
#include <iostream>
#include <QTextCodec>
//#include <QFile>
/* **
 * @name: class myApp
 * @Author: bdus
 * @time: 2018-8-6 17:23:54
 * @description:
 *        myAPP是一个单例类 用于描述软件本身的配置
 *

*/
typedef struct myAppData_{
    //       ========    Software    ========

    QString Path_App;                    //software root path

    //software configs
    QString AppTitle;                   //software name
    QString Path_layoutSaveto;                //path where to save the partition diagram file
    //QString Path_config;                //path where to save the app configuration file
    QString Name_config;// = "config.dat";                //filename of configration (.ini) file
    QString Path_ResultImg;             //path where to save the dection result
    //QString Path_log;


    // =========    Camera parameters   ========
        //参考SDK

    double ExposureTimeAbs;
    double GainRaw ;
    uint32_t Width;
    uint32_t Height ;

    // =========    layout file chosen   =========

    //QString Path_layoutSavto;
    QString Layout_name;    //正在使用的layout
    int Layout_index;
}myAppData;


class myApp : public QObject
{
    Q_OBJECT

public:
    static myApp * getInstance()
    {
        return m_pInstance;
    }
    static void Release()
    {
        if (m_pInstance != NULL)
        {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    }

    myAppData data;
    QSettings * setting;

    // ========    .ini file  ==========

    void ReadConfig(myApp *&ins);//,QString &path);
    void WriteConfig(myApp *&ins);//, QString &path);

private:
    //myApp(QObject *parent = 0);
    myApp();
    myApp(const myApp&) {}
    myApp& operator ==(const myApp&) {}

private:
    static myApp* m_pInstance;

};


#endif // MYAPP_H
