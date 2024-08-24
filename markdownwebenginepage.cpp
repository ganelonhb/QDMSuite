#include "markdownwebenginepage.h"

MarkdownWebEnginePage::MarkdownWebEnginePage(QObject *parent)
    : QWebEnginePage(parent)
{

}

bool MarkdownWebEnginePage::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
    Q_UNUSED(type);
    Q_UNUSED(isMainFrame);

    if (url.scheme() == QString("qrc"))
        return true;

    // handle scenario where link is to a document

    QDesktopServices::openUrl(url);

    return false;
}
