#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <algorithm>
#include <list>
#include <fstream>
#include <map>
#include <queue>
#include <cmath>
using namespace std;
//incompete declaration, because vertex and egde refer to each other
struct Vertex;

//Item in my adjList
struct Edge
{
    Vertex* dest;
    double distance;
    Edge(Vertex* dest = 0, double dist =0.0)
        : dest(dest), distance(dist)   { }
};

//Info for each Vertex
struct Vertex
{
    string name;
    double latitude;                    //breitengrad
    double longitude;                   //laengengrad
    vector<Edge> adjList;               //list of Edge objects; each contains internal vertices  und distance
    double dist;                        //store shortest path
    Vertex* prev;                       //previous vertex on the shortest path; use to store path in reverse order
    int scratch;                        //use in djistra
    Vertex(const string& name, double latitude, double longitude)
        :name(name), latitude(latitude), longitude(longitude)
    {
        reset();
    }
    void reset()
    {
        dist = INFINITY;
        prev = nullptr;
        scratch = 0;
    }
};

struct Path
{
    Vertex* destination;        //w
    double distance;            //distance to (w);-> d(w)=d(v)+cost(wv)
    Path(Vertex* dest = 0, double dist = 0.0)
        : destination(dest), distance(dist){ }

    bool operator> (const Path& path) const
    {
        return distance > path.distance;
    }

    bool operator< (const Path& path) const
    {
        return distance < path.distance;
    }

};

class Graph
{
public:
    Graph();
    ~Graph();
    double degreeToRad(double angle) const;
    double calcDist(const Vertex &startV, const Vertex &destV) const;
    void addEdge(const string& startName, const string& destName);
    void addVertex(const string& vertexName, double latitude, double longitude);
    Vertex* getVertex(const string& vertexName);
    vector<Vertex> getVertices();
    void reversePath(const Vertex& start, const Vertex& dest, vector<Vertex>& vertices) const;
    string printPath(const string& startName, const string& destName) const;
    void connectNearest(const string& startV);
    void clearAll();
    void djistra(const string& startName);
    void saveVertices();
    void saveEdges();
private:
    typedef map<string, Vertex*> vmap;
    vmap vertexMap;                                                                         //to store my map
};
#endif // GRAPH_H
