#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T11:08:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = DBOX-MTCT
TEMPLATE = app

DESTDIR = $$PWD

#QMAKE_LFLAGS += /STACK:64000000

SOURCES +=  main.cpp\
            mainwindow.cpp \
    graphics_view_zoom.cpp \
    MinutiaeMarker/minutiaemarker.cpp \
    mousefingerprintscene.cpp \
    networktrainer.cpp \
    minutiaechecker.cpp \
    caffenetwork.cpp \
    databasetester.cpp \
    isoconverter.cpp \
    QCustomPlot/qcustomplot.cpp \
    extractiontester.cpp \
    Config/dbox_mtct_config.cpp \
    Config/minutia_config.cpp \
    MinutiaeMarker/minutia.cpp \
    MinutiaeMarker/Config/minutiaemarker_config.cpp \
    MinutiaeMarker/minutiaemarker_settings.cpp \
    MinutiaeMarker/Utils/minutiaemarker_dataaugmentationutils.cpp \
    image.cpp \
    MinutiaeMarker/minutiaemarker_fileserializer.cpp

HEADERS  += mainwindow.h \
    graphics_view_zoom.h \
    MinutiaeMarker/minutiaemarker.h \
    mousefingerprintscene.h \
    networktrainer.h \
    minutiaechecker.h \
    caffenetwork.h \
    databasetester.h \
    isoconverter.h \
    qmatconverter.h \
    QCustomPlot/qcustomplot.h \
    extractiontester.h \
    helper.h \
    MinutiaeMarker/minutia.h \
    ui_mainwindow.h \
    Config/dbox_mtct_config.h \
    Config/minutia_config.h \
    MinutiaeMarker/minutiaemarker_settings.h \
    MinutiaeMarker/Utils/minutiaemarker_dataaugmentationutils.h \
    MinutiaeMarker/Config/minutiamarker_config.h \
    image.h \
    MinutiaeMarker/minutiaemarker_fileserializer.h

FORMS    += mainwindow.ui

#icons
RC_ICONS = core/config/Icons/mmtc.ico

#CUDA
unix:!macx: LIBS += -L/opt/cuda/lib64/ -lcudart
INCLUDEPATH += /opt/cuda/include
DEPENDPATH += /opt/cuda/include

#SupremaSensor
unix:!macx: LIBS += -L/usr/local/lib/ -lUFMatcher
INCLUDEPATH += /usr/local/include/suprema
DEPENDPATH += /usr/local/include/suprema

#OpenCV
unix:!macx: LIBS += -L/usr/lib/ -lopencv_core
unix:!macx: LIBS += -L/usr/lib/ -lopencv_imgcodecs
unix:!macx: LIBS += -L/usr/lib/ -lopencv_imgproc

#ArrayFire
unix:!macx: LIBS += -L/usr/lib/ -lafcuda

#Caffe
unix:!macx: LIBS += -L/usr/lib/ -lcaffe
unix:!macx: LIBS += -L/usr/lib/ -lboost_system
unix:!macx: LIBS += -L/usr/lib/ -lglog
unix:!macx: LIBS += -L/usr/lib/ -lprotobuf

#Extraction
unix:!macx: LIBS += -L$$PWD/../../Git/fingerprint-extraction-lib/ -lExtraction

INCLUDEPATH += $$PWD/../../Git/fingerprint-extraction-lib
DEPENDPATH += $$PWD/../../Git/fingerprint-extraction-lib

#Matcher
unix:!macx: LIBS += -L$$PWD/../../Git/fingerprint-matching-lib/ -lMatcher

INCLUDEPATH += $$PWD/../../Git/fingerprint-matching-lib
DEPENDPATH += $$PWD/../../Git/fingerprint-matching-lib

#Preprocessing
unix:!macx: LIBS += -L$$PWD/../../Git/fingerprint-preprocessing-lib/ -lPreprocessing

INCLUDEPATH += $$PWD/../../Git/fingerprint-preprocessing-lib
DEPENDPATH += $$PWD/../../Git/fingerprint-preprocessing-lib

RESOURCES +=

DISTFILES += \
    Resources/MinutiaeIcons/BIFURCATION.png \
    Resources/MinutiaeIcons/BREAK.png \
    Resources/MinutiaeIcons/BRIDGE.png \
    Resources/MinutiaeIcons/CROSSBAR.png \
    Resources/MinutiaeIcons/DOCK.png \
    Resources/MinutiaeIcons/DOT.png \
    Resources/MinutiaeIcons/ENCLOSURE.png \
    Resources/MinutiaeIcons/OPPOSITE_BIFURCATIONS.png \
    Resources/MinutiaeIcons/OVERLAP.png \
    Resources/MinutiaeIcons/RETURN.png \
    Resources/MinutiaeIcons/SHORT_RIDGE.png \
    Resources/MinutiaeIcons/SPIKE.png \
    Resources/MinutiaeIcons/TERMINATION.png \
    Resources/MinutiaeIcons/TRIFURCATION.png
