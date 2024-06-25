#include "fantasynamegeneratorwidget.h"
#include "ui_fantasynamegeneratorwidget.h"

FantasyNameGeneratorWidget::FantasyNameGeneratorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FantasyNameGeneratorWidget)
{
    ui->setupUi(this);

    QDir standardConfig(
        QDir::cleanPath(
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
        )
    );

    if (QDir d; !standardConfig.exists())
        d.mkdir(standardConfig.absolutePath());

    QDir nameGenerators(
        QDir::cleanPath(
            standardConfig.absolutePath()
            + QDir::separator()
            + "generators"
        )
    );

    if (QDir d; !nameGenerators.exists())
        d.mkdir(nameGenerators.absolutePath());

    this->generatorPath = nameGenerators;
}

FantasyNameGeneratorWidget::~FantasyNameGeneratorWidget()
{
    delete ui;
}
