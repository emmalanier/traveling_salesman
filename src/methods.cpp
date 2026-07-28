//METHODS.CPP//

//2do : implement constructors, CMake

#include "header.h"

destination:: destination()
{
    m_alt=0;
    m_name=" ";
}

destination::destination(coordinates coords, double alt, std::string name)
{
  m_coordinates=coords;
  m_alt=alt;
  m_name=name;
}

coordinates destination::get_coordinates()
{
  return m_coordinates;
}

double destination::get_alt()
{
  return m_alt;
}

std::string destination::get_name()
{
  return m_name;
}

void destination::set_coordinates(const coordinates& coordinates_var)
{
  m_coordinates = coordinates_var;
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

  m_coordinates.cart.x = EARTH_RADIUS * cos(m_coordinates.geo.longi.total_sec*SECOND) * cos(m_coordinates.geo.lat.total_sec*SECOND);
  m_coordinates.cart.y = EARTH_RADIUS * cos(m_coordinates.geo.lat.total_sec*SECOND) * sin(m_coordinates.geo.longi.total_sec*SECOND);
  m_coordinates.cart.z = EARTH_RADIUS * sin(m_coordinates.geo.lat.total_sec*SECOND);
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

  result = m_coordinates.geo.lat.degrees*3600 + m_coordinates.geo.lat.minutes*60 + m_coordinates.geo.lat.seconds;
  if(m_coordinates.geo.lat.is_positive==false)
  {
    result = -result;
  }

  m_coordinates.geo.lat.total_sec = result;

  result = 0;

  result = m_coordinates.geo.longi.degrees*3600 + m_coordinates.geo.longi.minutes*60 + m_coordinates.geo.longi.seconds;
  if(m_coordinates.geo.longi.is_positive==false)
  {
    result = -result;
  }

  m_coordinates.geo.longi.total_sec = result;
}


double cart_distance_between(const destination& dest_1, const destination& dest_2)
{
  double results;

  double x_dist = 0.0;
  double y_dist = 0.0;
  double z_dist = 0.0;

  x_dist = dest_1.get_coordinates().cart.x - dest_2.get_coordinates().cart.x;
  y_dist = dest_1.get_coordinates().cart.y - dest_2.get_coordinates().cart.y;
  z_dist = dest_1.get_coordinates().cart.z - dest_2.get_coordinates().cart.z;

  results = sqrt(x_dist*x_dist + y_dist*y_dist + z_dist*z_dist);

  return results;
}