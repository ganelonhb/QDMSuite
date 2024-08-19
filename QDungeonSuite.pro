QT       += core gui network svg qml openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2b

INCLUDEPATH += $$PWD/deps

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calcmenupushbutton.cpp \
    calculator2ndpushbutton.cpp \
    calculatorwidget.cpp \
    clickmenupushbutton.cpp \
    contextmenupushbutton.cpp \
    deps/htmlparser/html.cpp \
    diceroll.cpp \
    diceroll3dwidget.cpp \
    dicerolltracker.cpp \
    dicerollwidget.cpp \
    downloadsfaileddialogwidget.cpp \
    draggabletabbar.cpp \
    draggabletabwidget.cpp \
    exprtkengine.cpp \
    fantasynamegeneratordownloadwidget.cpp \
    fantasynamegeneratorhtmlparser.cpp \
    fantasynamegeneratorwidget.cpp \
    fnggeneratepagehtmlparser.cpp \
    fngitemmodel.cpp \
    genders.cpp \
    keypresseventfilter.cpp \
    linenumberarea.cpp \
    main.cpp \
    mainwindow.cpp \
    markdownedit.cpp \
    markdowneditorwidget.cpp \
    markdownhighlighter.cpp \
    model3d.cpp \
    qclickablelabel.cpp \
    splittabswidget.cpp \
    swearchecker.cpp \
    tabpressedeventfilter.cpp \
    treesortfilterproxymodel.cpp \
    welcomewidget.cpp

HEADERS += \
    calcmenupushbutton.h \
    calculator2ndpushbutton.h \
    calculatorwidget.h \
    clickmenupushbutton.h \
    contextmenupushbutton.h \
    deps/htmlparser/html.hpp \
    dice_roll.h \
    diceroll.h \
    diceroll3dwidget.h \
    dicerolltracker.h \
    dicerollwidget.h \
    downloadsfaileddialogwidget.h \
    draggabletabbar.h \
    draggabletabwidget.h \
    exprtk_methods.hpp \
    exprtkengine.h \
    exprtkexceptions.hpp \
    fantasynamegeneratordownloadwidget.h \
    fantasynamegeneratorhtmlparser.h \
    fantasynamegeneratorwidget.h \
    fnggeneratepagehtmlparser.h \
    fngitemmodel.h \
    genders.h \
    helper_functions.hpp \
    keypresseventfilter.h \
    linenumberarea.h \
    mainwindow.h \
    markdownedit.h \
    markdowneditorwidget.h \
    markdownhighlighter.h \
    model3d.h \
    qclickablelabel.h \
    qdmswidget.hpp \
    splittabswidget.h \
    swearchecker.h \
    tabpressedeventfilter.h \
    treesortfilterproxymodel.h \
    welcomewidget.h

FORMS += \
    calculatorwidget.ui \
    dicerollwidget.ui \
    downloadsfaileddialogwidget.ui \
    fantasynamegeneratordownloadwidget.ui \
    fantasynamegeneratorwidget.ui \
    mainwindow.ui \
    markdowneditorwidget.ui \
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

# Specify the path to the Assimp library and include directory
INCLUDEPATH += $$PWD/deps/assimp/include
LIBS += -L$$PWD/deps/assimp -lassimp

# Statically link libassimp.a
LIBS += $$PWD/deps/assimp/libassimp.a

# Dynamically link the dependencies of libassimp.a
LIBS += -lz -lpthread -ldl -lminizip
