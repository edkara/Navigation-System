#include "ort.h"

Ort::Ort()
{

}

Ort::Ort(double laengengrad, double breitengrad, int lastId, string name)
    :laengengrad(laengengrad), breitengrad(breitengrad), id(++lastId), name(name)
{

}

void Ort::set_laengengrad(double laengengrad)
{
    this->laengengrad=laengengrad;
}

double Ort::get_laengengrad() const
{
    return this->laengengrad;
}

void Ort::set_breitengrad(double breitengrad)
{
    this->breitengrad=breitengrad;
}

double Ort::get_breitengrad() const
{
    return this->breitengrad;
}

void Ort::set_id(int id)
{
    this->id=id;
}

int Ort::get_id() const
{
    return this->id;
}

void Ort::set_name(string name)
{
    this->name=name;
}

string Ort::get_name() const
{
    return this->name;
}

void Ort::save(ofstream &out)
{
    out.write(reinterpret_cast<char*>(&breitengrad),sizeof (double));
    out.write(reinterpret_cast<char*>(&laengengrad),sizeof (double));
    out.write(reinterpret_cast<char*>(&id),sizeof (int));

    size_t sizeName = this->name.size();
    out.write(reinterpret_cast<char*>(&sizeName),sizeof (size_t));
    out.write(reinterpret_cast<const char*>(name.c_str()), sizeName);

}

Ort::~Ort()
{

}
