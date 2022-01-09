QT       += core sql
QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    ask.cpp \
    introduct.cpp \
    introduction.cpp \
    kmp.cpp \
    login.cpp \
    main.cpp \
    map.cpp \
    md5.cpp \
    nearby.cpp \
    normalmap.cpp \
    privilegemap.cpp \
    privilegeregister.cpp \
    recommendation.cpp \
    register.cpp \
    widget.cpp

HEADERS += \
    account.h \
    ask.h \
    introduct.h \
    introduction.h \
    kmp.h \
    login.h \
    map.h \
    md5.h \
    nearby.h \
    normalmap.h \
    privilegemap.h \
    privilegeregister.h \
    recommendation.h \
    register.h \
    widget.h

FORMS += \
    account.ui \
    ask.ui \
    introduct.ui \
    introduction.ui \
    login.ui \
    map.ui \
    nearby.ui \
    normalmap.ui \
    privilegemap.ui \
    privilegeregister.ui \
    recommendation.ui \
    register.ui \
    widget.ui

RC_FILE = myapp.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
