#include "markdownhighlighter.h"

MarkdownHighlighter::MarkdownHighlighter(QObject *parent)
    : QSyntaxHighlighter{parent}
{
    initializeHtmlRules();
    initializeMarkdownRules();
}

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter{parent}
{
    initializeHtmlRules();
    initializeMarkdownRules();
}

void MarkdownHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, std::as_const(markdownRules))
        applyRule(text, rule);

    foreach(const HighlightingRule &rule, std::as_const(htmlRules))
        applyRule(text, rule);

    static QRegularExpression header1Underline(R"(^\s*=+\s*$)");
    static QRegularExpression header2Underline(R"(^\s*-+\s*$)");

    if (previousBlockState() == 1 && text.contains(header1Underline))
    {
        setFormat(0, currentBlock().previous().text().length(), multilineRules["header1AltFormat"]);
    }
    else if (previousBlockState() == 1 && text.contains(header2Underline))
    {
        setFormat(0, currentBlock().previous().text().length(), multilineRules["header2AltFormat"]);
    }

    setCurrentBlockState(0);

    if (text.contains(QRegularExpression(R"(^\s*.+\s*$)")))
    {
        if (currentBlock().next().text().contains(header1Underline) || currentBlock().next().text().contains(header2Underline))
        {
            setCurrentBlockState(1);
        }
    }
}

void MarkdownHighlighter::initializeMarkdownRules()
{
    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::ExtraBold);
    markdownRules.append({QRegularExpression(R"(^\s*#{1,6} .*)"), headerFormat});

    QTextCharFormat header1AltFormat;
    header1AltFormat.setFontWeight(QFont::ExtraBold);
    multilineRules.insert("header1AltFormat",header1AltFormat);

    QTextCharFormat header2AltFormat;
    header2AltFormat.setFontWeight(QFont::Bold);
    multilineRules.insert("header2AltFormat", header2AltFormat);

    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    markdownRules.append({QRegularExpression(R"((\*\*|__)(.*?)\1)"), boldFormat});

    QTextCharFormat italicFormat;
    italicFormat.setFontItalic(true);
    markdownRules.append({QRegularExpression(R"((\*|_)(.*?)\1)"), italicFormat});

    QTextCharFormat codeFormat;
    codeFormat.setFontFamilies(
        {
         "Courier New",
         "Courier",
         "Consolas",
         "Menlo",
         "Monaco",
         "Liberation Mono",
         "DejaVu Sans Mono",
         "Ubuntu Mono",
         "Source Code Pro",
         "FreeMono",
         "Andale Mono",
         "Linux Libertine Mono",
         "Bitstream Vera Sans Mono"
        }
    );
    markdownRules.append({QRegularExpression(R"(`([^`]*)`)"), codeFormat});

    QTextCharFormat blockQuoteFormat;
    blockQuoteFormat.setForeground(Qt::green);
    markdownRules.append({QRegularExpression(R"(^\s*>+\s*.*)"), blockQuoteFormat});

    QTextCharFormat hrFormat;
    hrFormat.setForeground(Qt::gray);
    markdownRules.append({QRegularExpression(R"(^\s*([-*_])\1{2,}\s*$)"), hrFormat});
}

void MarkdownHighlighter::initializeHtmlRules()
{

}

void MarkdownHighlighter::applyRule(const QString& text, const HighlightingRule &rule)
{
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);

    while (matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();

        setFormat(match.capturedStart(), match.capturedLength(), rule.format);
    }
}
