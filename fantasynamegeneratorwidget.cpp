#include "fantasynamegeneratorwidget.h"
#include "ui_fantasynamegeneratorwidget.h"

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
