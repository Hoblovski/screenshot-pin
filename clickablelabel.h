#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QWidget>

class ClickableLabel : public QLabel
{
    Q_OBJECT
signals:
    void clicked();
    void rightClicked();

protected:
    void virtual mousePressEvent(QMouseEvent* event);

public:
    explicit ClickableLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~ClickableLabel();
};

#endif // CLICKABLELABEL_H
