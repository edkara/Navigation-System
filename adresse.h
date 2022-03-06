#ifndef ADRESSE_H
#define ADRESSE_H
#include "ort.h"

class Adresse : public Ort
{
public:
    Adresse();
    Adresse(double laengengrad, double breitengrad, int id, string name, string strasse, int hausnummer, int postleitzahl, string gemeinde);
    void save(ofstream &out) override;
    void anzeigen();
    void set_strasse(string strasse);
    string get_strasse() const;
    void set_hausnummer(int hausnummer);
    int get_hausnummer() const;
    void set_postleitzahl(int postleitzahl);
    int get_postleitzahl() const;
    void set_gemeinde(string gemeinde);
    string get_gemeinde() const;
    ~Adresse() override;
private:
    string strasse;
    int hausnummer;
    int postleitzahl;
    string gemeinde;
};
#endif // ADRESSE_H


