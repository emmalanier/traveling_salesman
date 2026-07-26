//METHODS.CPP//

//2do : implement constructors, CMake

#include "header.h"

destination:: destination()
{
    m_lat=0;
    m_long=0;
    m_alt=0;
    m_name=" ";
}

destination::destination(double lat, double long, double alt, std::string name)
{
  m_lat=lat;
  m_long=long;
  m_alt=alt;
  m_name=name;
}

double destination::get_lat()
{
  return m_lat;
}

double destination::get_long()
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

void destination::set_lat(const double& lat)
{
  m_lat = lat;
}

void destination::set_long(const double& long)
{
  m_long = long;
}

void destination::set_alt(const double& alt)
{
  m_alt = alt;
}

void destination::set_name(const std::string& name)
{
  m_name = name;
}