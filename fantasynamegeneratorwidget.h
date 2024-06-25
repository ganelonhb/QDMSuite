#ifndef FANTASYNAMEGENERATORWIDGET_H
#define FANTASYNAMEGENERATORWIDGET_H

#include <QWidget>
#include <QStandardPaths>
#include <QDir>

namespace Ui {
class FantasyNameGeneratorWidget;
}

class FantasyNameGeneratorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FantasyNameGeneratorWidget(QWidget *parent = nullptr);
    ~FantasyNameGeneratorWidget();

private:
    Ui::FantasyNameGeneratorWidget *ui;

    QDir generatorPath;
};

#endif // FANTASYNAMEGENERATORWIDGET_H
