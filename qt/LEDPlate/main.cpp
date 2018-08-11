#include "mainwindow.h"
#include <QApplication>
//#include <QTextCodec> // Set string encoder

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //
    myApp * ins = myApp::getInstance();
    ins->Path_App = QDir::currentPath();
    ins->Path_layoutSaveto = "LayoutSave";


    //
    MainWindow w;
    w.show();

    return a.exec();
}
