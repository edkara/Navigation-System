#include "testDistance.h"
#include "graph.h"

void TestDistance::testDistOstWest()
{
    Graph g;
    Vertex* saarbruecken = new Vertex("Saarbruecken", 49.2401572, 6.9969327);
    Vertex* cottbus = new Vertex("Cottbus", 51.7563108, 14.3328679);
    double distSaCo = g.calcDist(*saarbruecken, *cottbus);

    QVERIFY( distSaCo > 561.0225 && distSaCo < 620.0775);
}

void TestDistance::testDistNordSued()
{
    Graph g;
    Vertex* kiel = new Vertex("Kiel", 54.3233, 10.1228);
    Vertex* muenchen = new Vertex("Muenchen", 48.135125, 11.581981);
    double distKiMu = g.calcDist(*kiel, *muenchen);
    QVERIFY( distKiMu > 658.4925 && distKiMu < 727.8075);
}
