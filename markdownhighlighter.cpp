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
}

void MarkdownHighlighter::initializeMarkdownRules()
{
    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::ExtraBold);
    markdownRules.append({ QRegularExpression(R"(^\s{0,3}#{1,6} .*)"), headerFormat });

    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    markdownRules.append({ QRegularExpression(R"((\*\*|__)(.*?)\1)"), boldFormat });

    QTextCharFormat italicFormat;
    italicFormat.setFontItalic(true);
    markdownRules.append({ QRegularExpression(R"((\*|_)(.*?)\1)"), italicFormat });

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
    markdownRules.append({ QRegularExpression(R"(`([^`]*)`)"), codeFormat });
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
