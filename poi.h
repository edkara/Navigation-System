#ifndef POI_H
#define POI_H
#include "ort.h"

class Poi : public Ort
{
public:
    Poi();
    Poi(double laengengrad, double breitengrad, int id, string name, string kategorie, string bemerkung);
    void save(ofstream &out) override;
    void anzeigen();
    void set_kategorie(string kategorie);
    string get_kategorie() const;
    void set_bemerkung(string bemerkung);
    string get_bemerkung() const;
    ~Poi() override;
private:
    string kategorie;
    string bemerkung;
};

#endif // POI_H
