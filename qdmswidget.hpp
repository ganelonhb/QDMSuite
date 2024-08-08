#ifndef QDMSWIDGET_H
#define QDMSWIDGET_H

#include <QWidget>
#include <QObject>

class QDMSWidget : public QWidget
{
    Q_OBJECT
public:
    QDMSWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
        :QWidget(parent, f) {}

    bool isCloseBlocked()
    {
        std::lock_guard<std::mutex> lock(mutex);
        return m_blockClose;
    }

    void blockClose()
    {
        std::lock_guard<std::mutex> lock(mutex);
        m_blockClose = true;
    }

    void unblockClose()
    {
        std::lock_guard<std::mutex> lock(mutex);
        m_blockClose = false;
    }

private:
    std::atomic<bool> m_blockClose;
    std::mutex mutex;
};

#endif // QDMSWIDGET_H
