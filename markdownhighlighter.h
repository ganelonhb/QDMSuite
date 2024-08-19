#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextDocument>
#include <QTextEdit>
#include <QTextCharFormat>
#include <QList>

class MarkdownHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    MarkdownHighlighter(QObject *parent);
    MarkdownHighlighter(QTextDocument *parent);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QList<HighlightingRule> markdownRules;
    QList<HighlightingRule> htmlRules;

    void initializeMarkdownRules();
    void initializeHtmlRules();
    void applyRule(const QString &text, const HighlightingRule &rule);
};

#endif // MARKDOWNHIGHLIGHTER_H
