#ifndef MARKDOWNWEBENGINEPAGE_H
#define MARKDOWNWEBENGINEPAGE_H

#include <QObject>
#include <QWebEnginePage>
#include <QDesktopServices>

class MarkdownWebEnginePage : public QWebEnginePage
{
    Q_OBJECT
public:
    explicit MarkdownWebEnginePage(QObject *parent = nullptr);

protected:
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);
};

#endif // MARKDOWNWEBENGINEPAGE_H
