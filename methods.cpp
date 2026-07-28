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

//Currently, for these methods, we are considering that the positions of the two destinations are at the same altitude, 0.0km

void destination::compute_cart_coordinates()
{
  this->convert_to_sec();

  m_lat.cart.x = EARTH_RADIUS * cos(m_lat.geo.total_sec*SECOND) * cos(m_long.geo.total_sec*SECOND);
  m_lat.cart.y = EARTH_RADIUS * cos(m_lat.geo.total_sec*SECOND) * sin(m_long.geo.total_sec*SECOND);
  m_lat.cart.z = EARTH_RADIUS * sin(m_lat.geo.total_sec*SECOND);
}

//double destination::cartesian_distance_to(destination& dest)
//{
//  double result;

//}

double destination::geodesic_distance_to(destination& dest)
{
  double result;


}

void destination::convert_to_sec()
{
  int result;

  result = m_lat.geo.degrees*3600 + m_lat.geo.minutes*60 + m_lat.geo.seconds;
  if(m_lat.geo.is_positive==false)
  {
    result = -result;
  }

  m_lat.geo.total_sec = result;

  result = 0;

  result = m_long.geo.degrees*3600 + m_long.geo.minutes*60 + m_long.geo.seconds;
  if(m_long.geo.is_positive==false)
  {
    result = -result;
  }

  m_long.geo.total_sec = result;
}


double cart_distance_between(const destination& dest_1, const destination& dest_2)
{
  double results;

  double x_dist = 0.0;
  double y_dist = 0.0;
  double z_dist = 0.0;

  x_dist = dest_1.get_lat().cart.x - dest_2.get_lat().cart.x;
  y_dist = dest_1.get_lat().cart.y - dest_2.get_lat().cart.y;
  z_dist = dest_1.get_lat().cart.z - dest_2.get_lat().cart.z;

  results = sqrt(x_dist*x_dist + y_dist*y_dist + z_dist*z_dist);

  return results;
}