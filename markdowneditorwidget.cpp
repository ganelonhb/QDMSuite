#include "markdowneditorwidget.h"
#include "ui_markdowneditorwidget.h"

MarkdownEditorWidget::MarkdownEditorWidget(QWidget *parent)
    : QDMSWidget(parent)
    , ui(new Ui::MarkdownEditorWidget)
{
    ui->setupUi(this);

    ui->preview->setContextMenuPolicy(Qt::NoContextMenu);

    MarkdownWebEnginePage *page = new MarkdownWebEnginePage(this);

    ui->preview->setPage(page);

    connect(ui->textEdit->document(), &QTextDocument::contentsChanged, this, &MarkdownEditorWidget::textChanged);

    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("content"), &content);
    page->setWebChannel(channel);

    content.setCss(theme());

    connect(&theme, &MarkdownThemeGetter::themeChanged, this, &MarkdownEditorWidget::cssChanged);

    ui->preview->setUrl(QUrl("qrc:/ui/qmarkdown/index.qtml"));
    ui->editCheckBox->setIcon(QIcon(":/ui/icons/symbolic-dark/pencil.svg"));

    ui->modeButton->setIcons(QIcon(":/ui/icons/symbolic-dark/code.svg"), QIcon(":/ui/icons/symbolic-dark/markdown.svg"));

    connect(ui->modeButton, &TriSwitch::positionChanged, this, &MarkdownEditorWidget::modeChanged);
}

void MarkdownEditorWidget::cssChanged()
{
    content.setCss(theme());
}

void MarkdownEditorWidget::textChanged()
{
    content.setText(ui->textEdit->document()->toPlainText());
}

void MarkdownEditorWidget::modeChanged(TriSwitchPosition pos)
{
    switch (pos)
    {
    case TriSwitchPosition::RIGHT:
        ui->markdownRendererWidget->setVisible(false);
        ui->textEdit->setVisible(true);
        return;
    case TriSwitchPosition::MIDDLE:
        ui->markdownRendererWidget->setVisible(true);
        ui->textEdit->setVisible(true);
        return;
    case TriSwitchPosition::LEFT:
        ui->markdownRendererWidget->setVisible(true);
        ui->textEdit->setVisible(false);
        return;
    }

    return;
}

MarkdownEditorWidget::~MarkdownEditorWidget()
{
    delete ui;
}

void MarkdownEditorWidget::on_comboBox_currentTextChanged(const QString &themeName)
{
    theme.setTheme(themeName);
}


void MarkdownEditorWidget::on_zoomSlider_sliderMoved(int position)
{
    double factor = position / 100.;

    ui->preview->setZoomFactor(factor);
    ui->zoomFactor->setText(QString::number(static_cast<int>(factor * 100)) + "%");
}


void MarkdownEditorWidget::on_resetFactor_clicked()
{
    ui->preview->setZoomFactor(1.0);
    ui->zoomFactor->setText("100%");

    ui->zoomSlider->blockSignals(true);
    ui->zoomSlider->setValue(100);
    ui->zoomSlider->blockSignals(false);
}


void MarkdownEditorWidget::on_zoomDown_clicked()
{
    qreal zoomFactor = ui->preview->zoomFactor();
    ui->preview->setZoomFactor(zoomFactor - .1);

    int sliderValue = ui->zoomSlider->value();
    ui->zoomSlider->blockSignals(true);
    ui->zoomSlider->setValue(sliderValue - 10);
    ui->zoomFactor->setText(QString::number(static_cast<int>((zoomFactor - .1) * 100)) + "%");
    ui->zoomSlider->blockSignals(false);
}


void MarkdownEditorWidget::on_zoomUp_clicked()
{
    qreal zoomFactor = ui->preview->zoomFactor();
    ui->preview->setZoomFactor(zoomFactor + .1);

    int sliderValue = ui->zoomSlider->value();
    ui->zoomSlider->blockSignals(true);
    ui->zoomSlider->setValue(sliderValue + 10);
    ui->zoomFactor->setText(QString::number(static_cast<int>((zoomFactor + .1) * 100)) + "%");
    ui->zoomSlider->blockSignals(false);
}
