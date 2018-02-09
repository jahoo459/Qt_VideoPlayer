#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T13:12:24
#
#-------------------------------------------------

QT       += core gui sql concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videoexplorerframe.cpp \
    videoplayerframe.cpp \
    videoplayer.cpp \
    labelsframe.cpp \
    configurelabelsdialog.cpp \
    categorycounterframe.cpp \
    newprojectdialog.cpp \
    dbmanager.cpp \
    historywindow.cpp

HEADERS  += mainwindow.h \
    videoexplorerframe.h \
    videoplayerframe.h \
    videoplayer.h \
    labelsframe.h \
    configurelabelsdialog.h \
    categorycounterframe.h \
    newprojectdialog.h \
    dbmanager.h \
    historywindow.h

FORMS    += \
    videoexplorerframe.ui \
    videoplayerframe.ui \
    labelsframe.ui \
    configurelabelsdialog.ui \
    categorycounterframe.ui \
    newprojectdialog.ui \
    historywindow.ui


INCLUDEPATH += D:\OpenCV\mingw32_build\install\include
LIBS += -LD:\OpenCV\mingw32_build\install\x86\mingw\lib \
    -lopencv_core320.dll \
    -lopencv_highgui320.dll \
    -lopencv_imgcodecs320.dll \
    -lopencv_imgproc320.dll \
    -lopencv_features2d320.dll \
    -lopencv_calib3d320.dll \
    -lopencv_videoio320.dll \
    -lopencv_video320.dll \
    -lopencv_videostab320.dll

RESOURCES += \
    resources/icons.qrc
