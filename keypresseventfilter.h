#ifndef KEYPRESSEVENTFILTER_H
#define KEYPRESSEVENTFILTER_H

#include <QObject>
#include <QList>
#include <QEvent>
#include <QKeyEvent>

class KeyPressEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit KeyPressEventFilter(Qt::Key key = Qt::Key_Enter, QObject *parent = nullptr);
    KeyPressEventFilter(QList<Qt::Key> keys, QObject *parent = nullptr);

signals:
    void triggered();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QList<Qt::Key> keys;
};

#endif // KEYPRESSEVENTFILTER_H
