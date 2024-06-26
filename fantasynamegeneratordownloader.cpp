#include "fantasynamegeneratordownloader.h"

FantasyNameGeneratorDownloader::FantasyNameGeneratorDownloader() {
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

    QDir fantasyNameGenerators(
        QDir::cleanPath(
            nameGenerators.absolutePath()
            + QDir::separator()
            + "FantasyNameGenerators"
        )
    );

    if (QDir d; !fantasyNameGenerators.exists())
        d.mkdir(fantasyNameGenerators.absolutePath());

    this->generatorPath = fantasyNameGenerators;
}
