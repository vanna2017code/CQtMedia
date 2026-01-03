#pragma once
#include <QWidget>
#include <QVector>
#include "AIEngine.h"

class ChapterBar : public QWidget {
    Q_OBJECT
public:
    explicit ChapterBar(QWidget* parent = nullptr);
    void setChapters(const QVector<Chapter>& chapters, qint64 durationMs);

signals:
    void chapterClicked(qint64 positionMs);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QVector<Chapter> chapters;
    qint64 duration = 0;
    QString hoverText;
};
