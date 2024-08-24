#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>

class Document : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER m_text WRITE setText NOTIFY textChanged FINAL)
    Q_PROPERTY(QString css MEMBER m_css WRITE setCss NOTIFY cssChanged)
public:
    explicit Document(QObject *parent = nullptr);

    void setText(const QString &text);
    void setCss(const QString &css);
signals:
    void textChanged(const QString &text);
    void cssChanged(const QString &css);

private:
    QString m_text;
    QString m_css;
};

#endif // DOCUMENT_H
