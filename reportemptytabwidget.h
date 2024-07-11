#ifndef REPORTEMPTYTABWIDGET_H
#define REPORTEMPTYTABWIDGET_H

#include <QObject>
#include <QTabWidget>

class ReportEmptyTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    ReportEmptyTabWidget(QWidget *parent = nullptr);

signals:
    void reportEmpty(QWidget *w = nullptr);

protected:
    virtual void tabRemoved(int index) override;
};

#endif // REPORTEMPTYTABWIDGET_H
