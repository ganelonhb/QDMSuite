#include "reportemptytabwidget.h"

ReportEmptyTabWidget::ReportEmptyTabWidget(QWidget *parent)
    : QTabWidget(parent)
{}

void ReportEmptyTabWidget::tabRemoved(int index)
{
    QTabWidget::tabRemoved(index);

    if (!this->count()) emit reportEmpty(this);
}
