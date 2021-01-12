#ifndef QGAMEUTILS_H
#define QGAMEUTILS_H

#include <QString>
#include <QList>
#include <QStringList>
#include <QPair>
#include <QDebug>
#include <QtGlobal>
#include <QRandomGenerator>

class QGameUtils
{
public:
    QGameUtils();

    static void initRand(uint seed);
    static int rand(int min, int max);
    static qreal rand(qreal min, qreal max);
    static QString rand(int Ln = 12);
private:
    static uint _seed;
    static bool _is_seed_set;
};

#endif // QGAMEUTILS_H
