QT += core
QT -= widgets
QT -= gui

TEMPLATE = lib
DEFINES += G3DTLAS_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Point/laspoint.cpp \
    VLR/lasvlr.cpp \
    VLR/lasvlrgeokeys.cpp \
    lasevlr.cpp \
    lasfile.cpp \
    lasfileheader.cpp

HEADERS += \
    Point/laspoint.h \
    Point/laspoint0.h \
    Point/laspoint1.h \
    Point/laspoint10.h \
    Point/laspoint2.h \
    Point/laspoint3.h \
    Point/laspoint4.h \
    Point/laspoint5.h \
    Point/laspoint6.h \
    Point/laspoint7.h \
    Point/laspoint8.h \
    Point/laspoint9.h \
    VLR/lasvlr.h \
    VLR/lasvlrclassificationlookup.h \
    VLR/lasvlrgeokeyentry.h \
    VLR/lasvlrgeokeys.h \
    VLR/lasvlrheader.h \
    VLR/lasvlrpointextrabytes.h \
    VLR/lasvlrsuperseded.h \
    VLR/lasvlrtextarea.h \
    VLR/lasvlrwaveformpacketdescriptor.h \
    g3dtlas.h \
    g3dtlas_global.h \
    lasevlr.h \
    lasfile.h \
    lasfileheader.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    licence.txt
