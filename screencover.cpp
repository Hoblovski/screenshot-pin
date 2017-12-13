#include "screencover.h"

#include <QFrame>
#include <QPainter>
#include <QVBoxLayout>

ScreenCover::ScreenCover(QWidget *parent):
    QWidget(parent),
    m_rubberBand(new QRubberBand(QRubberBand::Rectangle, this))
{
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    setLayout(vlayout);

    QFrame *frame = new QFrame(this);
    frame->setMinimumSize(300, 300);
    vlayout->addWidget(frame);

    QPalette pal;
    pal.setBrush(QPalette::Highlight, QBrush(QColor(0, 0, 0, 0))); //Qt::transparent));
    m_rubberBand->setPalette(pal);

    m_rubberBand->setWindowOpacity(0.0);

    setWindowFlags(Qt::WindowStaysOnTopHint
                   | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
}

ScreenCover::~ScreenCover()
{
}

void ScreenCover::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
        case Qt::LeftButton:{
            origin = event->pos();
            m_rubberBand->setGeometry(QRect(origin, QSize()));
            m_rubberBand->show();
            break;}
        case Qt::RightButton:{
            emit selectionCanceled();
            break;}
        default:
            break;
    }
}

void ScreenCover::mouseMoveEvent(QMouseEvent *event)
{
    m_rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
}

void ScreenCover::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) return;
    m_rubberBand->hide();
    QRect geom = m_rubberBand->geometry();
    emit selectionComplete(geom.x(), geom.y(), geom.width(), geom.height());
}

void ScreenCover::paintEvent(QPaintEvent */*event*/)
{
    QColor bgColor = palette().background().color();
    bgColor.setAlpha(kAlphaBackground);
    QPainter painter(this);
    painter.fillRect(rect(), bgColor);
}
