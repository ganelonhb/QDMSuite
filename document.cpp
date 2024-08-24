#include "document.h"

Document::Document(QObject *parent)
    : QObject{parent}
{}

void Document::setText(const QString &text)
{
    if (text == m_text) return;

    m_text = text;
    emit textChanged(m_text);
}

void Document::setCss(const QString &css)
{
    if (css == m_css) return;

    m_css = css;
    emit textChanged(m_css);
}
