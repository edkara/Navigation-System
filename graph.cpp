#include "graph.h"

Graph::Graph()
{

}

double Graph::degreeToRad(double angle) const
{
    return M_PI * angle / 180.0;
}

double Graph::calcDist(const Vertex &startV, const Vertex &destV) const
{
    double latRad1 = degreeToRad(startV.latitude);
    double latRad2 = degreeToRad(destV.latitude);
    double lonRad1 = degreeToRad(startV.longitude);
    double lonRad2 = degreeToRad(destV.longitude);

    double diffLa = latRad2 - latRad1;
    double doffLo = lonRad2 - lonRad1;

    double computation = asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));
    return 2 * 6372.8 * computation;
}

void Graph::addEdge(const string &startName, const string &destName)
{
    Vertex* start = getVertex(startName);
    Vertex* destination = getVertex(destName);
    double distance = calcDist(*start,*destination);
    start->adjList.push_back(Edge(destination, distance));
}

void Graph::addVertex(const string &vertexName, double latitude, double longitude)
{
    vmap::iterator itr = vertexMap.find(vertexName);
    if(itr==vertexMap.end())
    {
        Vertex* newV = new Vertex(vertexName, latitude, longitude);
        vertexMap[vertexName] = newV;
    }
}

Vertex* Graph::getVertex(const string &vertexName)
{
    vmap::iterator itr = vertexMap.find(vertexName);
    return (*itr).second;
}

vector<Vertex> Graph::getVertices()
{
    vector<Vertex> storeVertices;
    for(vmap::iterator itr = vertexMap.begin(); itr!=vertexMap.end(); ++itr)
    {
        Vertex& w = *(*itr).second;
        storeVertices.push_back(w);
    }
    return storeVertices;
}

void Graph::reversePath(const Vertex &start, const Vertex &dest, vector<Vertex>& vertices) const
{
    if(dest.prev!=&start)
    {
        reversePath(start,*dest.prev, vertices);
    }
    vertices.push_back(dest);
}

string Graph::printPath(const string& startName, const string &destName) const
{
    string storePaths;
    double distance = 0.0;
    vector<Vertex> store;
    vmap::const_iterator itr_first = vertexMap.find(startName);
    const Vertex& startVertex = *(*itr_first).second;

    vmap::const_iterator itr = vertexMap.find(destName);
    if(itr==vertexMap.end())
    {
        cout << "Destination vertex not found!\n";
    }
    const Vertex& w = *(*itr).second;
    if(w.dist==INFINITY)
    {
        //cout << destName << " is unreachable!\n";
    }
    else
    {
        distance = w.dist;
        reversePath(startVertex, w, store);
    }
    storePaths = "Entfernung von " + startName + " bis " + destName+ " ist " + to_string(distance) + " km.\n\n";
    storePaths += "Von "+startName+ " bis: \n";
    for (unsigned int i = 0; i<store.size(); ++i) {
        storePaths += to_string(i+1)+". "+store[i].name+" insgesamt "+to_string(store[i].dist)+" km.\n";
    }
    return storePaths;
}

void Graph::connectNearest(const string& startV)
{
    vmap::iterator itr_find = vertexMap.find(startV);
    const Vertex& u = *(*itr_find).second;

    vector<Vertex> nearestVertices;
    vector<pair<double, string>> allVertices;
    for(vmap::iterator itr = vertexMap.begin(); itr!=vertexMap.end(); ++itr)
    {
        Vertex& w = *(*itr).second;
        if(w.name!=startV)
        {
            double distance = calcDist(u,w);
            allVertices.push_back(make_pair(distance,w.name));
        }
    }
    sort(allVertices.begin(), allVertices.end());
    addEdge(startV, allVertices.at(0).second);
    addEdge(allVertices.at(0).second, startV);
}

void Graph::clearAll()
{
    for(vmap::iterator itr = vertexMap.begin(); itr!=vertexMap.end(); ++itr)
    {
        (*itr).second->reset();
    }
}

void Graph::djistra(const string& startName)
{
    priority_queue<Path, vector<Path>, greater<Path>> myPaths;
    Path bestPath;
    vmap::iterator itr = vertexMap.find(startName);
    if(itr==vertexMap.end())
    {
        cout << startName+" is not a vertex" << endl;
    }
    clearAll();
    Vertex* start = (*itr).second;
    myPaths.push(Path(start,0));
    start->dist = 0;
    unsigned int nodesSeen = 0;
    for( ; nodesSeen < vertexMap.size(); nodesSeen++)
    {
        do
        {
            if(myPaths.empty())
            {
                return;
            }
            bestPath = myPaths.top();
            myPaths.pop();
        } while(bestPath.destination->scratch!=0);
        Vertex* v = bestPath.destination;
        v->scratch = 1;
        for(unsigned int i = 0; i < v->adjList.size(); i++)
        {
            Edge e = v->adjList[i];
            Vertex* destination = e.dest;
            double dist = e.distance;

            if(dist<0)
            {
                cout << "negative Edge\n";
            }
            if(destination->dist > v->dist+dist)
            {
                destination->dist = v->dist+dist;
                destination->prev = v;
                myPaths.push(Path(destination, destination->dist));
            }
        }
    }
}

void Graph::saveVertices()
{
    ofstream graphVertices;
    graphVertices.open("D:/QTProjects/myVertices.txt", fstream::out|fstream::trunc);
    if(!graphVertices)
    {
        cerr << "Unable to open myVertices.txt!\n";
    }
    for(vmap::iterator itr = vertexMap.begin(); itr!=vertexMap.end(); ++itr)
    {
        graphVertices <<(*itr).second->name<<";"<<(*itr).second->latitude<<";"<<(*itr).second->longitude << endl;
    }
    graphVertices.close();
}

void Graph::saveEdges()
{
    ofstream graphEdges;
    graphEdges.open("D:/QTProjects/myEdges.txt", fstream::out|fstream::trunc);
    if(!graphEdges)
    {
        cerr << "Unable to open myEdges.txt!\n";
    }
    for(vmap::iterator itr = vertexMap.begin(); itr!=vertexMap.end(); ++itr)
    {
        for(unsigned int i = 0; i<(*itr).second->adjList.size();i++)
        {
            graphEdges <<(*itr).second->name<<";"<<(*itr).second->adjList.at(i).dest->name<<endl;
        }
    }
    graphEdges.close();
}

Graph::~Graph()
{
    for(vmap::iterator itr = vertexMap.begin(); itr!=vertexMap.end(); ++itr)
    {
        delete (*itr).second;
    }
}
