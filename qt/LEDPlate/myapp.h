#ifndef MYAPP_H
#define MYAPP_H
#include <QObject>
#include <QString>
#include <QSettings>

/* **
 * @name: class myApp
 * @Author: bdus
 * @time: 2018-8-6 17:23:54
 * @description:
 *        myAPP是一个单例类 用于描述软件本身的配置
 *

*/

class myApp : public QObject
{
    Q_OBJECT

public:
    //static myApp * Instance();


    //System info
    QString Path_App;                    //software root path


    //software configs
    QString AppTitle;                   //software name
    QString Path_layout;                //path where to save the partition diagram file
    //QString Path_config;                //path where to save the app configuration file
    //const QString Name_config;                //filename of configration (.ini) file
    QString Path_ResultImg;             //path where to save the dection result
    QString Path_log;


    void ReadConfig();
    void WriteConfig();

private:
    myApp()
    {
        //init
        ;

    }

    ~myApp();

};

//const QString myApp::Name_config = "config.ini";

#endif // MYAPP_H
