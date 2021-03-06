/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "screencover.h"
#include "screenshot.h"

#include "windows.h"


Screenshot::Screenshot() :
    originalPixmap(1, 1),
    screenshotLabel(new QLabel(this)),
    mouseClicked(false),
    scov(new ScreenCover(0))
{
    screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    screenshotLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(screenshotLabel);

    QSizeGrip *szGrip = new QSizeGrip(this);

    setWindowTitle(tr("Screenshot"));
    setMinimumSize(100, 100);
    SetForegroundWindow((HWND)winId());
    setWindowFlags(Qt::WindowStaysOnTopHint
                   | Qt::FramelessWindowHint);
}


void Screenshot::resizeEvent(QResizeEvent * /* event */)
{
    QSize scaledSize = originalPixmap.size();
    scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);
    if (!screenshotLabel->pixmap() || scaledSize != screenshotLabel->pixmap()->size())
        updateScreenshotLabel();
}

void Screenshot::mousePressEvent(QMouseEvent *event)
{
//    qDebug() << "mousePressEvent\n";
    switch (event->button()) {
        case Qt::LeftButton:{
            m_mousePressPos = QPoint(event->x(), event->y());
            mouseMoveSinceClick = false;
            mouseClicked = true;
            break;}
        case Qt::RightButton:
            close();
            break;
        default:
            break;
    }
}

void Screenshot::mouseReleaseEvent(QMouseEvent *event)
{
//    qDebug() << "mouseReleaseEvent\n";
    switch (event->button()) {
        case Qt::LeftButton:{
            QPoint pos = QPoint(event->x(), event->y());
            if (!mouseMoveSinceClick)
                newScreenShot();
            mouseClicked = false;
            break;}
        default:
            break;
    }
}

void Screenshot::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug() << "mouseMoveEvent\n";
    if (!mouseClicked) return;
    QPoint deltaPos = event->globalPos() - m_mousePressPos;
    mouseMoveSinceClick = true;
    move(deltaPos);
}

void Screenshot::newScreenShot()
{
    scov->showFullScreen();
    connect(scov, &ScreenCover::selectionComplete, this, &Screenshot::onSelectionComplete);
    connect(scov, &ScreenCover::selectionCanceled, this, &Screenshot::onSelectionCalceled);
    hide();
}

void Screenshot::onSelectionComplete(int x, int y, int w, int h)
{
    scov->close();

    QScreen *screen = QGuiApplication::primaryScreen();
    if (const QWindow *window = windowHandle())
        screen = window->screen();
    if (!screen)
        return;

    originalPixmap = screen->grabWindow(0, x, y, w, h);

    show();

    updateScreenshotLabel();
    resize(originalPixmap.size());
    setMinimumSize(originalPixmap.size() / 8);
}

void Screenshot::onSelectionCalceled()
{
    scov->close();

    show();

    updateScreenshotLabel();
    resize(originalPixmap.size());
    setMinimumSize(originalPixmap.size() / 8);
}


void Screenshot::updateScreenshotLabel()
{
    screenshotLabel->setPixmap(originalPixmap.scaled(screenshotLabel->size(),
                                                     Qt::KeepAspectRatio,
                                                     Qt::SmoothTransformation));
}

