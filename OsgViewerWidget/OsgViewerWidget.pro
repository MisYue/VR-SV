# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = OsgViewerWidget
DESTDIR = ../Debug
QT += core gui xml xmlpatterns
CONFIG += staticlib
DEFINES += QT_DLL QT_XML_LIB QT_XMLPATTERNS_LIB OSGVIEWERWIDGET_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
PRECOMPILED_HEADER = StdAfx.h
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(OsgViewerWidget.pri)
