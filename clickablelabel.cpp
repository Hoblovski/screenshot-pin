#include "clickablelabel.h"

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
        case Qt::LeftButton:
            emit clicked();
            break;
        case Qt::RightButton:
            emit rightClicked();
            break;
        default:
            // ignore
            break;
    }
}

ClickableLabel::ClickableLabel(QWidget *parent, Qt::WindowFlags f) :
    QLabel(parent, f)
{
}

ClickableLabel::~ClickableLabel()
{
}
