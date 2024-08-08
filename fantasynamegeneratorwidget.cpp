#include "fantasynamegeneratorwidget.h"
#include "ui_fantasynamegeneratorwidget.h"

#include <iostream>

FantasyNameGeneratorWidget::FantasyNameGeneratorWidget(QWidget *parent)
    : QDMSWidget(parent)
    , ui(new Ui::FantasyNameGeneratorWidget)
{
    ui->setupUi(this);

    this->dl = new FantasyNameGeneratorDownloadWidget(this, Qt::WindowFlags() | Qt::Window);
    this->ui->downloadPushButton->setEnabled(false);

    connect(this->dl, &FantasyNameGeneratorDownloadWidget::downloadComplete, this, &FantasyNameGeneratorWidget::on_fngDone);
    this->dl->download();

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &FantasyNameGeneratorWidget::timer_timeout);
    timer->start(5000);

    connect(dl, &FantasyNameGeneratorDownloadWidget::blockClose, this, &FantasyNameGeneratorWidget::onDlBlockClose);
    connect(dl, &FantasyNameGeneratorDownloadWidget::unblockClose, this, &FantasyNameGeneratorWidget::onDlUnblockClose);

    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir appDataDir(appDataPath);

    if (!appDataDir.exists())
        appDataDir.mkpath(".");

    QString fngPath = appDataPath + QDir::separator() + "fng";
    QDir fngDir(fngPath);

    if (!fngDir.exists())
        fngDir.mkpath(".");

    model = new FNGItemModel(this);
    model->setRootDirectory(fngDir.absolutePath());

    ui->treeView->setModel(model);

    buttonGroup = new QButtonGroup(this);

    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &FantasyNameGeneratorWidget::onSelectionChanged);

    jse = nullptr;
    ui->generateButton->setEnabled(false);
}

void FantasyNameGeneratorWidget::timer_timeout()
{
    if (this->ui->downloadPushButton->isEnabled())
        return;
    this->dl->download();
    timer->start(5000);
}

FantasyNameGeneratorWidget::~FantasyNameGeneratorWidget()
{
    delete ui;
}

void FantasyNameGeneratorWidget::on_downloadPushButton_clicked()
{
    this->dl->show();
}

void FantasyNameGeneratorWidget::on_fngDone(bool success)
{
    this->ui->downloadPushButton->setEnabled(success);
}

void FantasyNameGeneratorWidget::onDlBlockClose()
{
    blockClose();
}

void FantasyNameGeneratorWidget::onDlUnblockClose()
{
    unblockClose();
}

void FantasyNameGeneratorWidget::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    QModelIndexList selectedIndexes = selected.indexes();

    for (int i = 0; i < buttonGroup->buttons().size(); ++i)
    {
        QAbstractButton *button = buttonGroup->buttons().at(i);
        ui->genderLayout->removeWidget(button);
        button->deleteLater();
    }

    delete buttonGroup;
    buttonGroup = new QButtonGroup(this);

    delete jse;
    jse = new QJSEngine(this);


    if (!selectedIndexes.isEmpty())
    {
        QModelIndex index = selectedIndexes.first();

        QString path = static_cast<FileNode *>(index.internalPointer())->path;
        QString file = path + QDir::separator() + "meta.toml";
        if (QFile(file).exists())
        {
            try
            {
                std::shared_ptr<cpptoml::table> meta_toml = cpptoml::parse_file(file.toStdString());

                QString name = QString::fromStdString(*meta_toml->get_as<std::string>("name"));
                ui->generatorNameLabel->setText(name);

                QString script = path + QDir::separator() + QString::fromStdString(*meta_toml->get_as<std::string>("script"));

                jse->importModule(script);

                std::shared_ptr<cpptoml::table> genders = meta_toml->get_table("genders");

                for (const std::pair<const std::basic_string<char>, std::shared_ptr<cpptoml::base>> &element : *genders)
                {
                    QString buttonText = QString::fromStdString(element.second->as<std::string>()->get());

                    QRadioButton *button = new QRadioButton(this);
                    button->setText(buttonText);

                    button->setProperty("value", QString::fromStdString(element.first));

                    buttonGroup->addButton(button);
                    ui->genderLayout->addWidget(button);
                }

                buttonGroup->buttons().at(0)->setChecked(true);

                ui->generateButton->setEnabled(true);
            }
            catch (const cpptoml::parse_exception &e)
            {
                QMessageBox::warning(this, "Could not parse .toml", "Could not parse the toml file " + file + ".\nError: " + QString::fromLatin1(e.what()));
                ui->generateButton->setEnabled(false);
            }
        }
        else
        {
            ui->generateButton->setEnabled(false);
            ui->generatorNameLabel->setText("No Generator Selected");
        }

        return;
    }


}

