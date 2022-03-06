#ifndef ORT_H
#define ORT_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

class Ort
{
public:
    Ort();
    Ort(double laengengrad, double breitengrad, int lastId, string name);
    void set_laengengrad(double laengengrad);
    double get_laengengrad() const;
    void set_breitengrad(double breitengrad);
    double get_breitengrad() const;
    void set_id(int id);
    int get_id() const;
    void set_name(string name);
    string get_name() const;
    virtual void save(ofstream &out);
    virtual ~Ort();
private:
    double laengengrad;
    double breitengrad;
    int id;
    string name;
};

inline double degree_to_radian(double angle)
{
    return M_PI * angle / 180.0;
}

inline double entfernung_berechnen(const Ort& first_point, const Ort& second_point)
{
    double latRad1 = degree_to_radian(first_point.get_breitengrad());
    double latRad2 = degree_to_radian(second_point.get_breitengrad());
    double lonRad1 = degree_to_radian(first_point.get_laengengrad());
    double lonRad2 = degree_to_radian(second_point.get_laengengrad());

    double diffLa = latRad2 - latRad1;
    double doffLo = lonRad2 - lonRad1;

    double computation = asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));
    return 2 * 6372.8 * computation;
}
#endif // ORT_H
