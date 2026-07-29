//METHODS.CPP//

//2do : minimisation, checking units

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
  convert_to_sec();
  m_coordinates.cart.x = EARTH_RADIUS * cos(m_coordinates.geo.longi.total_sec*SECOND) * cos(m_coordinates.geo.lat.total_sec*SECOND);
  m_coordinates.cart.y = EARTH_RADIUS * cos(m_coordinates.geo.lat.total_sec*SECOND) * sin(m_coordinates.geo.longi.total_sec*SECOND);
  m_coordinates.cart.z = EARTH_RADIUS * sin(m_coordinates.geo.lat.total_sec*SECOND);
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


double cart_distance_between(destination& dest_1, destination& dest_2)
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

double geodesic_distance_between(destination& dest_1, destination& dest_2)
{
  double result = 0.0;
  double cart_dist = 0.0;
  double half_cart_dist = 0.0;
  double central_angle = 0.0;

  cart_dist = cart_distance_between(dest_1, dest_2);
  half_cart_dist = cart_dist / 2.0;
  central_angle = 2.0*(asin(half_cart_dist / EARTH_RADIUS));

  result = central_angle * (2.0*M_PI*EARTH_RADIUS);

  return result;
}

std::vector<destination> optimised_route_1(std::vector<destination>& vec, destination& start)
{
  double shortest_distance = 0.0;
  double current_distance = 0.0;

  destination closest_step;
  int closest_step_index = 0;

  std::vector<destination> results;
  results.push_back(start);
  destination last_step = start;
  std::vector<destination> steps_left = vec;

  rm_start(steps_left, start);

  while(steps_left.size() > 0)
  {
    //Take last results element
    last_step = results.back();

    shortest_distance = geodesic_distance_between(last_step, steps_left[0]);
    //Compute distance to all elements in vec (will need optimization)
    for(int i=1; i<steps_left.size(); i++)
    {
      current_distance = geodesic_distance_between(last_step, steps_left[i]);

      if(current_distance < shortest_distance)
      {
        shortest_distance = current_distance;
        closest_step = steps_left[i];
        closest_step_index = i;
      }
    }

    //Take closest element and push to results
    results.push_back(closest_step);

    //Remove from vec
    steps_left.erase(steps_left.begin() + closest_step_index);

  }

  return results;
}

std::vector<destination> optimised_route_2(std::vector<destination>& vec, destination& start)
{
  std::vector<destination> results;
  int start_index = get_start_index(vec, start);
  destination inter_var = vec[0];

  vec[0] = start;
  vec[start_index] = inter_var;

  double current_route_distance = 0.0;
  double shortest_route_distance = 0.0;

  int possibilities = factorial(vec.size()-1);

  for(int i=0; i<possibilities; i++)
  {
    for(int j=0; j<vec.size()-1; j++)
    {
      current_route_distance += geodesic_distance_between(vec[j], vec[j+1]);
    }

    if(current_route_distance < shortest_route_distance || i==0)
    {
      shortest_route_distance = current_route_distance;
      results = vec;
    }

    current_route_distance = 0.0;
  }




  return results;
}

std::vector<std::string> read_inputs_from_file(std::string filename)
{
  std::vector<std::string> results;
  return results;
}

std::vector<destination> format_inputs(std::vector<std::string>& vec)
{
  std::vector<destination> results;

  return results;
}

void rm_start(std::vector<destination>& vec, destination& start)
{
  for(int i=0; i<vec.size(); i++)
  {
    if(vec[i].get_name() == start.get_name())
    {
      vec.erase(vec.begin() + i);
      break;
    }
  }
}

int get_start_index(std::vector<destination>& vec, destination& start)
{
  int result = 0;

  for(int i=0; i<vec.size(); i++)
  {
    if(vec[i].get_name() == start.get_name())
    {
      result = i;
      break;
    }
  }

  return result;
}

int factorial(int n)
{
  int result = 1;

  for(int i=1; i<=n; i++)
  {
    result *= i;
  }

  return result;
}

void permutate(std::vector<destination>& vec, int index_1, int index_2)
{
  destination inter_var = vec[index_1];
  vec[index_1] = vec[index_2];
  vec[index_2] = inter_var;
}