#include "keypresseventfilter.h"

KeyPressEventFilter::KeyPressEventFilter(Qt::Key key, QObject *parent)
    : QObject{parent}
{
    keys.append(key);
}

KeyPressEventFilter::KeyPressEventFilter(QList<Qt::Key> keys, QObject *parent)
    : QObject{parent}
    , keys(keys)
{}

bool KeyPressEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        foreach (Qt::Key key , keys)
        {
            if (keyEvent->key() == key)
            {
                emit triggered();
                return true;
            }
        }
    }

    return QObject::eventFilter(obj, event);
}
