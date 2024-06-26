#ifndef FANTASYNAMEGENERATORDOWNLOADER_H
#define FANTASYNAMEGENERATORDOWNLOADER_H

#include <QDir>
#include <QStandardPaths>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include "genderflags.h"

// This class will crawl FantasyNameGenerator and download .js files to
// the program data location.

class FantasyNameGeneratorDownloader
{
public:
    using NameGenderFlags = FantasyNameGender::namegenderflags_t;

    FantasyNameGeneratorDownloader();

signals:
    void replyRecieved(QNetworkReply reply);
    void fileDownloaded();
    void homeCrawled(QNetworkReply reply);

private slots:
    void saveJsFile(/*file type*/) const {}

private:
    const QList<QString> crawlHome() const;
    NameGenderFlags guessGenders(/*DOM element for generator page*/) const;

    QDir generatorPath;
};

#endif // FANTASYNAMEGENERATORDOWNLOADER_H
