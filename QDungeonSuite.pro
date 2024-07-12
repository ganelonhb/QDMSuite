QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

INCLUDEPATH += $$PWD/deps

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clickmenupushbutton.cpp \
    contextmenupushbutton.cpp \
    deps/htmlparser/html.cpp \
    diceroll.cpp \
    dicerolltracker.cpp \
    dicerollwidget.cpp \
    exprtkengine.cpp \
    exprtkparseexception.cpp \
    fantasynamegeneratordownloadwidget.cpp \
    fantasynamegeneratorhtmlparser.cpp \
    fantasynamegeneratorwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    qclickablelabel.cpp \
    splittabswidget.cpp \
    swearchecker.cpp \
    welcomewidget.cpp

HEADERS += \
    clickmenupushbutton.h \
    contextmenupushbutton.h \
    deps/htmlparser/html.hpp \
    dice_roll.h \
    diceroll.h \
    dicerolltracker.h \
    dicerollwidget.h \
    exprtkengine.h \
    exprtkparseexception.h \
    fantasynamegeneratordownloadwidget.h \
    fantasynamegeneratorhtmlparser.h \
    fantasynamegeneratorwidget.h \
    genderflags.h \
    mainwindow.h \
    qclickablelabel.h \
    splittabswidget.h \
    swearchecker.h \
    welcomewidget.h

FORMS += \
    dicerollwidget.ui \
    fantasynamegeneratordownloadwidget.ui \
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
