#include "ChapterBar.h"
#include <QPainter>
#include <QMouseEvent>
#include <QToolTip>

ChapterBar::ChapterBar(QWidget* parent) : QWidget(parent) {
    setMinimumHeight(24);
    setMouseTracking(true);
}

void ChapterBar::setChapters(const QVector<Chapter>& chaps, qint64 dur) {
    chapters = chaps;
    duration = dur;
    update();
}

void ChapterBar::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QLinearGradient grad(0,0,width(),0);
    grad.setColorAt(0, QColor("#2d2d2d"));
    grad.setColorAt(1, QColor("#1e1e1e"));
    p.fillRect(rect(), grad);

    if (duration <= 0) return;
    for (int i = 0; i < chapters.size(); ++i) {
        const auto&
