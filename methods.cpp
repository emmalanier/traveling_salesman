//METHODS.CPP//

//2do : implement constructors, CMake

#include "header.h"

destination:: destination()
{
    m_alt=0;
    m_name=" ";
}

destination::destination(coordinate lat, coordinate longitude, double alt, std::string name)
{
  m_lat=lat;
  m_long=longitude;
  m_alt=alt;
  m_name=name;
}

coordinate destination::get_lat()
{
  return m_lat;
}

coordinate destination::get_long()
{
  return m_long;
}

double destination::get_alt()
{
  return m_alt;
}

std::string destination::get_name()
{
  return m_name;
}

void destination::set_lat(const coordinate& lat)
{
  m_lat = lat;
}

void destination::set_long(const coordinate& longitude)
{
  m_long = longitude;
}

void destination::set_alt(const double& alt)
{
  m_alt = alt;
}

void destination::set_name(const std::string& name)
{
  m_name = name;
}

double destination::geodesic_distance_to(destination& dest)
{
  double result;

}
