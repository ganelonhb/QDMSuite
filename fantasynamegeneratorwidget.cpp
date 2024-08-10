#include "fantasynamegeneratorwidget.h"
#include "helper_functions.hpp"
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

    buttonGroup = new QButtonGroup(this);

    jse = nullptr;
    ui->generateButton->setEnabled(false);

    module = nullptr;

    int fontId = QFontDatabase::addApplicationFont(":/ui/fonts/Berylium/Berylium Rg.otf");

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont fantasieFont = QFont(fontFamily);

    QFontInfo fontInfo(fantasieFont);
    int pointSize = 16;

    if (fontInfo.pixelSize() > 0 && fontInfo.pointSize() == 0)
    {
        int dpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();

        int pixelSize = static_cast<int>((pointSize * dpi) / 72);

        fantasieFont.setPixelSize(pixelSize);
    }
    else
    {
        fantasieFont.setPointSize(pointSize);
    }

    ui->nameTextEdit->setFont(fantasieFont);

    fontId = QFontDatabase::addApplicationFont(":/ui/fonts/cardinal/Cardinal.ttf");
    pointSize = 14;

    fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    fantasieFont = QFont(fontFamily);

    if (fontInfo.pixelSize() > 0 && fontInfo.pointSize() == 0)
    {
        int dpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();

        int pixelSize = static_cast<int>((pointSize * dpi) / 72);

        fantasieFont.setPixelSize(pixelSize);
    }
    else
    {
        fantasieFont.setPointSize(pointSize);
    }

    ui->titleLabel->setFont(fantasieFont);

    QTextDocument *doc = ui->nameTextEdit->document();

    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignCenter);
    doc->setDefaultTextOption(QTextOption(Qt::AlignCenter));

    QLineEdit *searchView = ui->searchView;

    proxyModel = new TreeSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->treeView->setModel(proxyModel);

    connect(searchView, &QLineEdit::textEdited, proxyModel, &TreeSortFilterProxyModel::setFilterFixedString);

    QCompleter *completer = new QCompleter(proxyModel, this);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    searchView->setCompleter(completer);

    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &FantasyNameGeneratorWidget::onSelectionChanged);
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
    if (module) delete module;
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

    if (jse) delete jse;
    jse = new QJSEngine(this);

    jse->globalObject().setProperty("names", "");
    jse->globalObject().setProperty("nMs", "");
    jse->globalObject().setProperty("nm", "");
    jse->globalObject().setProperty("name", "");


    if (!selectedIndexes.isEmpty())
    {
        QModelIndex proxyIndex = selectedIndexes.first();
        QModelIndex index = proxyModel->mapToSource(proxyIndex);

        QString path = static_cast<FileNode *>(index.internalPointer())->path;
        QString file = path + QDir::separator() + "meta.toml";
        if (QFile(file).exists())
        {
            try
            {
                if (module) delete module;
                std::shared_ptr<cpptoml::table> meta_toml = cpptoml::parse_file(file.toStdString());

                QString name = QString::fromStdString(*meta_toml->get_as<std::string>("name"));
                ui->generatorNameLabel->setText(name);

                QString script = path + QDir::separator() + QString::fromStdString(*meta_toml->get_as<std::string>("script"));


                QFile scriptFile(script);

                if (!scriptFile.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    QMessageBox::warning(this, "Could not Read", "The script file:\n" + script + "\ncould not be read.");
                    ui->nameTextEdit->setText("No Generator Selected");
                    return;
                }

                QTextStream stream(&scriptFile);

                QString contents = stream.readAll();

                jse->evaluate(contents);

                std::shared_ptr<cpptoml::table> genders = meta_toml->get_table("genders");

                bool large = *meta_toml->get_as<bool>("large");

                for (const std::pair<const std::basic_string<char>, std::shared_ptr<cpptoml::base>> &element : *genders)
                {
                    QString buttonText = QString::fromStdString(element.second->as<std::string>()->get());

                    QRadioButton *button = new QRadioButton(this);
                    button->setText(buttonText);

                    button->setProperty("gender", QString::fromStdString(element.first));
                    button->setProperty("script", script);
                    button->setProperty("large", large);

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
                if (module) delete module;
                module = nullptr;
            }
        }
        else
        {
            ui->generateButton->setEnabled(false);
            ui->generatorNameLabel->setText("No Generator Selected");
            if (module) delete module;
            module = nullptr;
        }

        return;
    }
}


void FantasyNameGeneratorWidget::on_generateButton_clicked()
{
    ui->nameTextEdit->setText("");

    QList<QAbstractButton *> buttons = buttonGroup->buttons();

    if (buttons.empty())
        return;

    QString pass;
    QString script;
    bool large = false;
    foreach(const QAbstractButton * button, buttons)
    {
        if (button->isChecked())
        {
            pass = button->property("gender").toString();
            script = button->property("script").toString();
            large = button->property("large").toBool();
            break;
        }
    }

    QStringList namesList;
    for(int i = 0; i < ui->generateSpinBox->value(); ++i){
        QString name;

        int maxOut = 0;
        do
        {
            name = jse->evaluate("nameGen(" + pass + ");").toString();
        } while (name == "" && maxOut <= 5);

        if (maxOut == 5)
            name = "Error: Generator returns empty string.";

        namesList << name;
    }

    bool first = true;

    foreach (const QString &name, namesList)
    {
        QString sep = first ? "" : (large ? "\n\n" : "\n");
        if (first) first = false;

        QString nameFinal = addSpacesToNameAndSimplify(name);

        if (!large)
            nameFinal = makeCaps(nameFinal);

        ui->nameTextEdit->setText(ui->nameTextEdit->document()->toPlainText() + sep + nameFinal);
    }

    return;
}


void FantasyNameGeneratorWidget::on_clearPushButton_clicked()
{
    ui->nameTextEdit->setText("");
}

