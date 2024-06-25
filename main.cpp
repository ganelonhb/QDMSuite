#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>
#include <QStandardPaths>
#include "fantasynamegeneratorwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FantasyNameGeneratorWidget retard;

    QCoreApplication::setApplicationName("qdms");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QDungeonSuite_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
