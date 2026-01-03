#include "AIEngine.h"
#include <algorithm>
#include <QFileInfo>

AIEngine::AIEngine(QObject* parent) : QObject(parent) {}

QVector<Chapter> AIEngine::detectChapters(const QVector<float>& rms, int sampleRate, int hopMs, qint64 durationMs) {
    QVector<Chapter> chapters;
    if (rms.isEmpty()) return chapters;

    QVector<float> sorted = rms;
    std::sort(sorted.begin(), sorted.end());
    float median = sorted[sorted.size()/2];
    float thresh = median * 0.6f;

    qint64 posMs = 0;
    bool inSilence = false;
    qint64 startSilence = 0;

    for (int i = 0; i < rms.size(); ++i) {
        bool low = rms[i] < thresh;
        if (low && !inSilence) {
            inSilence = true;
            startSilence = posMs;
        } else if (!low && inSilence) {
            inSilence = false;
            qint64 endSilence = posMs;
            if (endSilence - startSilence >= 1500)
                chapters.push_back({startSilence, endSilence, "Silence"});
        }
        posMs += hopMs;
    }

    if (inSilence) {
        qint64 endSilence = durationMs;
        if (endSilence - startSilence >= 1500)
            chapters.push_back({startSilence, endSilence, "Silence"});
    }

    QVector<Chapter> boundaries;
    qint64 prev = 0;
    for (const auto& s : chapters) {
        if (s.startMs - prev > 3000)
            boundaries.push_back({prev, s.startMs, "Chapter"});
        prev = s.endMs;
    }
    if (durationMs - prev > 3000)
        boundaries.push_back({prev, durationMs, "Chapter"});
    return boundaries;
}

QPair<qint64, qint64> AIEngine::introOutroSkip(const QVector<Chapter>& chapters, qint64 durationMs) {
    if (chapters.isEmpty()) return {0,0};
    qint64 introEnd = 0;
    qint64 outroStart = durationMs;
    if (chapters.front().endMs - chapters.front().startMs < 15000)
        introEnd = chapters.front().endMs;
    if (chapters.back().endMs - chapters.back().startMs < 20000)
        outroStart = chapters.back().startMs;
    return {introEnd, outroStart};
}

QStringList AIEngine::recommend(const QStringList& playlist, const QString& current, const QMap<QString,int>& watchCounts) {
    struct Item { QString path; int score; };
    QList<Item> items;
    for (const auto& p : playlist) {
        if (p == current) continue;
        int dist = levenshtein(QFileInfo(p).baseName(), QFileInfo(current).baseName());
        int count = watchCounts.value(p, 0);
        int score = dist + count * 2;
        items.push_back({p, score});
    }
    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b){ return a.score < b.score; });
    QStringList out;
    for (int i = 0; i < std::min(5, items.size()); ++i) out << items[i].path;
    return out;
}

QStringList AIEngine::fuzzySearch(const QStringList& playlist, const QString& query) {
    QList<QPair<QString,int>> ranked;
    for (const auto& p : playlist) {
        int d = levenshtein(QFileInfo(p).fileName().toLower(), query.toLower());
        ranked.push_back({p, d});
    }
    std::sort(ranked.begin(), ranked.end(), [](auto& a, auto& b){ return a.second < b.second; });
    QStringList out;
    for (int i = 0; i < std::min(10, ranked.size()); ++i) out << ranked[i].first;
    return out;
}

int AIEngine::levenshtein(const QString& a, const QString& b) {
    const int n = a.size(), m = b.size();
    QVector<int> prev(m+1), cur(m+1);
    for (int j = 0; j <= m; ++j) prev[j] = j;
    for (int i = 1; i <= n; ++i) {
        cur[0] = i;
        for (int j = 1; j <= m; ++j) {
            int cost = (a[i-1] == b[j-1]) ? 0 : 1;
            cur[j] = std::min({ prev[j] + 1, cur[j-1] + 1, prev[j-1] + cost });
        }
        std::swap(prev, cur);
    }
    return prev[m];
}
