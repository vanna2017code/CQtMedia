#pragma once
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QPair>
#include <QMap>

struct Chapter {
    qint64 startMs;
    qint64 endMs;
    QString label;
};

class AIEngine : public QObject {
    Q_OBJECT
public:
    explicit AIEngine(QObject* parent = nullptr);

    QVector<Chapter> detectChapters(const QVector<float>& rms, int sampleRate, int hopMs, qint64 durationMs);
    QPair<qint64, qint64> introOutroSkip(const QVector<Chapter>& chapters, qint64 durationMs);
    QStringList recommend(const QStringList& playlist, const QString& current, const QMap<QString,int>& watchCounts);
    QStringList fuzzySearch(const QStringList& playlist, const QString& query);

private:
    int levenshtein(const QString& a, const QString& b);
};
