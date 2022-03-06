#include "adresse.h"

Adresse::Adresse()
{

}

Adresse::Adresse(double laengengrad, double breitengrad, int id, string name, string strasse, int hausnummer, int postleitzahl, string gemeinde)
    :Ort{laengengrad, breitengrad, id, name}
{
    this->strasse=strasse;
    this->hausnummer=hausnummer;
    this->postleitzahl=postleitzahl;
    this->gemeinde=gemeinde;
}

void Adresse::save(ofstream &out)
{
    Ort::save(out);
    size_t sizeStrasse = this->strasse.size();
    size_t sizeGemeinde = this->gemeinde.size();

    out.write(reinterpret_cast<char*>(&sizeStrasse),sizeof (size_t));
    out.write(reinterpret_cast<const char*>(strasse.c_str()), sizeStrasse);

    out.write(reinterpret_cast<char*>(&hausnummer),sizeof (int));
    out.write(reinterpret_cast<char*>(&postleitzahl),sizeof (int));

    out.write((char*)(&sizeGemeinde),sizeof (size_t));
    out.write((const char*)(gemeinde.c_str()), sizeGemeinde);
}

void Adresse::anzeigen()
{
    cout <<setw(2) << setfill(' ') << left << this->get_id()
        <<"| "<< setw(3) << setfill(' ') << left << "Adr"
        <<"| " << setw(13) << setfill(' ') << left << this->get_name()
        <<"| "<< setw(7) << setfill(' ') << left << this->get_breitengrad()
        <<"| "<< setw(7) << setfill(' ') << left << this->get_laengengrad()
        <<"| "<< this->get_strasse() << " " << this->get_hausnummer();
    if(this->get_postleitzahl() < 10000)
    {
        cout << ", "<< "0"+to_string(this->get_postleitzahl())<< " " << this->get_gemeinde() << "\n";
    }
    else
    {
        cout << ", "<< this->get_postleitzahl()<< " " << this->get_gemeinde() << "\n";
    }
}

void Adresse::set_strasse(string strasse)
{
    this->strasse=strasse;
}

string Adresse::get_strasse() const
{
    return this->strasse;
}

void Adresse::set_hausnummer(int hausnummer)
{
    this->hausnummer=hausnummer;
}

int Adresse::get_hausnummer() const
{
    return this->hausnummer;
}

void Adresse::set_postleitzahl(int postleitzahl)
{
    this->postleitzahl=postleitzahl;
}

int Adresse::get_postleitzahl() const
{
    return this->postleitzahl;
}

void Adresse::set_gemeinde(string gemeinde)
{
    this->gemeinde=gemeinde;
}

string Adresse::get_gemeinde() const
{
    return this->gemeinde;
}

Adresse::~Adresse()
{

}
