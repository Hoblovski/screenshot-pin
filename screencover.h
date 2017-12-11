#ifndef SCREENCOVER_H
#define SCREENCOVER_H

#include <QMouseEvent>
#include <QPushButton>
#include <QRubberBand>
#include <QWidget>

class ScreenCover : public QWidget
{
    Q_OBJECT
public:
    static const int kAlphaBackground = 1;

public:
    explicit ScreenCover(QWidget *parent = 0);
    ~ScreenCover();

public slots:

signals:
    void selectionComplete(int x, int y, int w, int h);

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent*);


private:
    QRubberBand* m_rubberBand;
    QPoint origin;
};

#endif // SCREENCOVER_H
