#include "navigation.h"
#include "testDistance.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Navigation w;
    w.show();
    TestDistance t;
    QTest::qExec(&t);
    return a.exec();
}
