QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dicedockwidget.cpp \
    diceroll.cpp \
    dicerolltracker.cpp \
    exprtkengine.cpp \
    exprtkparseexception.cpp \
    fantasynamegeneratorwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    qclickablelabel.cpp \
    swearchecker.cpp \
    welcomewidget.cpp

HEADERS += \
    dice_roll.h \
    dicedockwidget.h \
    diceroll.h \
    dicerolltracker.h \
    exprtk/exprtk.hpp \
    exprtkengine.h \
    exprtkparseexception.h \
    fantasynamegeneratorwidget.h \
    mainwindow.h \
    qclickablelabel.h \
    swearchecker.h \
    welcomewidget.h

FORMS += \
    dicedockwidget.ui \
    fantasynamegeneratorwidget.ui \
    mainwindow.ui \
    welcomewidget.ui

TRANSLATIONS += \
    QDungeonSuite_en_US.ts \
    QDungeonSuite_ja_JP.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
