#-------------------------------------------------
#
# Project created by QtCreator 2018-08-06T15:55:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LEDPlate
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#--------------------------------------------Basler Camera-------------------------------------------
INCLUDEPATH += $$PWD/include
LIBS += -L$$PWD/lib/x64 -lGCBase_MD_VC120_v3_0_Basler_pylon_v5_0 -lGenApi_MD_VC120_v3_0_Basler_pylon_v5_0 -lPylonBase_MD_VC120_v5_0 -lPylonC_MD_VC120 -lPylonGUI_MD_VC120_v5_0 -lPylonUtility_MD_VC120_v5_0
#----------------------------------------------------------------------------------------------

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    myapp.cpp \
    form_setting.cpp \
    form_cam.cpp \
    form_layout.cpp \
    form_product.cpp \
    form_count.cpp \
    cqlabel.cpp \
    sbaslercameracontrol.cpp \
    form_product.cpp

HEADERS += \
        mainwindow.h \
    form_setting.h \
    form_cam.h \
    form_layout.h \
    form_product.h \
    form_count.h \
    myapp.h \
    utilize.h \
    cqlabel.h \
    sbaslercameracontrol.h \
    form_product.h


FORMS += \
        mainwindow.ui \
    form_setting.ui \
    form_cam.ui \
    form_layout.ui \
    form_product.ui \
    form_count.ui \
    form_product.ui



#--------------------------------------------Basler Camera-------------------------------------------
INCLUDEPATH += $$PWD/include
LIBS += -L$$PWD/lib/x64 -lGCBase_MD_VC120_v3_0_Basler_pylon_v5_0 -lGenApi_MD_VC120_v3_0_Basler_pylon_v5_0 -lPylonBase_MD_VC120_v5_0 -lPylonC_MD_VC120 -lPylonGUI_MD_VC120_v5_0 -lPylonUtility_MD_VC120_v5_0

#INCLUDEPATH += E:\lcx\project\LEDPlate\LEDPLate\qt\LEDPlate\include
#LIBS += -LE:\lcx\project\LEDPlate\LEDPLate\qt\LEDPlate\lib\x64 -lGCBase_MD_VC120_v3_0_Basler_pylon_v5_0 -lGenApi_MD_VC120_v3_0_Basler_pylon_v5_0 -lPylonBase_MD_VC120_v5_0 -lPylonC_MD_VC120 -lPylonGUI_MD_VC120_v5_0 -lPylonUtility_MD_VC120_v5_0

#INCLUDEPATH += $$quote(D:\Program Files (x86)\led_sdk\Development\include)
#LIBS += $$quote(D:\Program Files (x86)\led_sdk\Development\lib\x64\*.lib)

#----------------------------------------------------------------------------------------------
