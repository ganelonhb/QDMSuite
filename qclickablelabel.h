#ifndef QCLICKABLELABEL_H
#define QCLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class QClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit QClickableLabel(QWidget* parent = nullptr);
    ~QClickableLabel();

signals:
    void clicked();
    void pressed();
    void released();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif // QCLICKABLELABEL_H
