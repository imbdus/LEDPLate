#ifndef UTILIZE_H
#define UTILIZE_H
#include <QDebug>
#include <QObject>
#include <QRect>
#include <QList>
#include <QDir>
#include <QFile>
#include <QMessageBox>

#define mmsg(X) QMessageBox::information(NULL,"message",X);
/* **
 * @name: class utilize
 * @Author: bdus
 * @time: 2018-8-7 20:04:52
 * @description:
 *        utilize是一个实用类 包含一些有用的定义
 *

*/

//typedef struct _rectangle
//{
//    int x;
//    int y;
//}rect;
//typedef QList<rect> layout;



class utilize : public QObject
{
public:

    //文件是否存在
    static bool FileIsExist(QString strFile) {
        QFile tempFile(strFile);
        return tempFile.exists();
    }

    //文件夹是否存在
    static bool FolderIsExist(QString strFolder) {
        QDir tempFolder(strFolder);
        return tempFolder.exists();
    }

    static bool Mkdir(QString &foldername) {
        QDir tmpfolder(foldername);
        if(false == tmpfolder.exists())
            return tmpfolder.mkdir(foldername);
        return 0;
    }

    static bool getLayout(QVector<QRect> &mylayout, QString &path) {
        QFile fp(path);
        if(false == fp.exists())
            return false;
        if(!fp.open(QIODevice::ReadOnly))
            return false;
        else {
            mylayout.clear();
            int x,y,w,h;
            while (!fp.atEnd()) {
                QByteArray line = fp.readLine();
                char * str = line.data();
                sscanf(str,"%d %d %d %d",&x,&y,&w,&h);
                //qDebug() << x + ' ' + y + ' ' + w  + ' ' + h <<'\n';
                mmsg(str)
                //delete(str);
                mylayout.append(QRect(x,y,w,h));
            }
        }

    }




};
#endif // UTILIZE_H
