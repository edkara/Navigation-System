#ifndef TESTDISTANCE_H
#define TESTDISTANCE_H
#include <QtTest/QTest>
#include "navigation.h"

class TestDistance : public QObject
{
    Q_OBJECT
private slots:
    void testDistOstWest();
    void testDistNordSued();
public:

};

#endif // TESTDISTANCE_H
