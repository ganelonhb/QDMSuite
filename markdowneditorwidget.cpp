#include "markdowneditorwidget.h"
#include "ui_markdowneditorwidget.h"

#include <iostream>

MarkdownEditorWidget::MarkdownEditorWidget(QWidget *parent)
    : QDMSWidget(parent)
    , ui(new Ui::MarkdownEditorWidget)
{
    ui->setupUi(this);

    ui->preview->setContextMenuPolicy(Qt::NoContextMenu);

    MarkdownWebEnginePage *page = new MarkdownWebEnginePage(this);

    ui->preview->setPage(page);

    ui->frame->setAutoFillBackground(true);
    QPalette textEditPallete = ui->textEdit->palette();
    textEditPallete.setColor(QPalette::Window, ui->frame->style()->standardPalette().color(QPalette::Base));
    ui->frame->setPalette(textEditPallete);

    QFrame *frame = ui->frame;

    auto colorFix = [](const QString &s) -> QString {
        return QString("#%1%2%3%4")
            .arg(s.mid(3, 2))
            .arg(s.mid(5, 2))
            .arg(s.mid(7, 2))
            .arg(s.mid(1, 2));
    };

    QPalette palette = frame->palette();
    QColor bgColor = palette.color(frame->backgroundRole());
    QString bg = colorFix(bgColor.name(QColor::HexArgb));

    QColor textColor(QApplication::palette().color(QPalette::Text));
    QString defaultText = colorFix(textColor.name(QColor::HexArgb));

    QColor linkColor(QApplication::palette().color(QPalette::Link));
    QColor linkVisitedColor(QApplication::palette().color(QPalette::LinkVisited));
    QString link = colorFix(linkColor.name(QColor::HexArgb));
    QString linkVisited = colorFix(linkVisitedColor.name(QColor::HexArgb));

    QColor accentColor(QApplication::palette().color(QPalette::Accent));
    QString accent = colorFix(accentColor.name(QColor::HexArgb));

    QFont font = QApplication::font();
    QFontInfo fontInfo(font);
    QString fontName = fontInfo.family();

    QFile qss(":/ui/qmarkdown/markdown.qss");
    if (!qss.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Somehow, we could not read the qrc file!";

    QString qssText = QString(qss.readAll())
                          .replace("<BACKGROUND_COLOR>", bg)
                          .replace("<DEFAULT_TEXT>", defaultText)
                          .replace("<FONT>", fontName)
                          .replace("<BLOCK_QUOTE_CITE>", accent)
                          .replace("<LINK>", link)
                          .replace("<LINK_VISITED>", linkVisited)
                          .replace("<BLOCK_QUOTE_COLOR>", accent);

    std::cout << qssText.toStdString() << std::endl;
    qss.close();

    connect(ui->textEdit->document(), &QTextDocument::contentsChanged, [this]() {content.setText(ui->textEdit->document()->toPlainText());});
    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("content"), &content);
    page->setWebChannel(channel);

    content.setCss(qssText);

    ui->preview->setUrl(QUrl("qrc:/ui/qmarkdown/index.qtml"));
}

MarkdownEditorWidget::~MarkdownEditorWidget()
{
    delete ui;
}
