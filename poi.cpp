#include "poi.h"

Poi::Poi()
{

}

Poi::Poi(double laengengrad, double breitengrad, int id, string name,string kategorie, string bemerkung)
    :Ort{laengengrad, breitengrad, id, name}
{
    this->kategorie=kategorie;
    this->bemerkung=bemerkung;
}

void Poi::save(ofstream &out)
{
    Ort::save(out);
    size_t sizeKategorie = this->kategorie.size();
    size_t sizeBemerkung = this->bemerkung.size();
    out.write(reinterpret_cast<char*>(&sizeKategorie),sizeof (size_t));
    out.write(reinterpret_cast<const char*>(kategorie.c_str()), sizeKategorie);

    out.write(reinterpret_cast<char*>(&sizeBemerkung),sizeof (size_t));
    out.write(reinterpret_cast<const char*>(bemerkung.c_str()), sizeBemerkung);
}

void Poi::anzeigen()
{
    cout <<setw(2) << setfill(' ') << left << this->get_id()
         <<"| " << setw(3) << setfill(' ') << left << "PoI"
         <<"| " << setw(13) << setfill(' ') << left << this->get_name()
         <<"| " << setw(7) << setfill(' ') << left << this->get_breitengrad()
         <<"| " << setw(7) << setfill(' ') << left << this->get_laengengrad()
         <<"| " << this->get_kategorie() << ", " << this->get_bemerkung() << "\n";
}

void Poi::set_kategorie(string kategorie)
{
    this->kategorie=kategorie;
}

string Poi::get_kategorie() const
{
    return this->kategorie;
}

void Poi::set_bemerkung(string bemerkung)
{
    this->bemerkung=bemerkung;
}

string Poi::get_bemerkung() const
{
    return this->bemerkung;
}

Poi::~Poi()
{

}
