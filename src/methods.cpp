//METHODS.CPP//


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
  m_coordinates.cart.x = EARTH_RADIUS * cos(m_coordinates.geo.longi.total_sec*SECOND*(M_PI/180)) * cos(m_coordinates.geo.lat.total_sec*SECOND*(M_PI/180))*1.0;
  m_coordinates.cart.y = EARTH_RADIUS * cos(m_coordinates.geo.lat.total_sec*SECOND*(M_PI/180)) * sin(m_coordinates.geo.longi.total_sec*SECOND*(M_PI/180))*1.0;
  m_coordinates.cart.z = EARTH_RADIUS * sin(m_coordinates.geo.lat.total_sec*SECOND*(M_PI/180))*1.0;
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

  std::cout << "Cartesian distance between " << dest_1.get_name() << " and " << dest_2.get_name() << " is : " << results << std::endl;

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

  std::cout << "Central angle between " << dest_1.get_name() << " and " << dest_2.get_name() << " is : " << central_angle << std::endl;

  result = central_angle * EARTH_RADIUS;

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

  std::vector<destination> current_route = vec;

  double current_route_distance = 0.0;
  double shortest_route_distance = 0.0;

  do
  {
    for(int i=0; i<vec.size()-1; i++)
    {
      current_route_distance += geodesic_distance_between(current_route[i], current_route[i+1]);
    }

    if(current_route_distance < shortest_route_distance)
    {
      shortest_route_distance = current_route_distance;
      results = current_route;
    }

    current_route_distance = 0.0;
  }while(std::next_permutation(current_route.begin()+1, current_route.end()));

  return results;
}

std::vector<std::string> read_inputs_from_file(const std::string& filename)
{
  std::vector<std::string> results;

  std::ifstream file(filename);
  std::string buffer;
  if(file.is_open())
  {
    while(getline(file, buffer))
      {
        results.push_back(buffer);
      }
    file.close();
  }

  else
  {
    std::cerr << "Unable to open file " << filename << std::endl ;
  }

  return results;
}

std::vector<destination> format_inputs(std::vector<std::string>& vec)
{
  std::vector<destination> results;

  for(int i=0; i<vec.size(); i++)
  {
    results.push_back(format_line(vec[i]));
  }


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

destination format_line(std::string& line_to_format)
{
  destination result;
  std::string name;
  std::string buffer;
  coordinates my_coord;
  geodesic_coordinates geo_coord ;
  int index = 0;
  bool deg_found = false;
  bool min_found = false;
  bool sec_found = false;

  for(int i=0 ; i<line_to_format.size(); i++)
  {
    if(line_to_format[i] == ':')
    {
      index=i;
      break;
    }

    name += line_to_format[i];
  }
  result.set_name(name);

  for(int i=index ; i<line_to_format.size(); i++)
  {
    if(line_to_format[i] == '}')
    {
      index = i+1 ;
      break;
    }

    if(isdigit(line_to_format[i]))
    {
      buffer += line_to_format[i];
    }

    else if(isalpha(line_to_format[i]))
    {
      if(line_to_format[i]=='N')
      {
        geo_coord.lat.is_positive=true;
      }

      else if(line_to_format[i]=='S')
      {
        geo_coord.lat.is_positive=false;
      }
    }

    else if(line_to_format[i] == 176)
    {
      deg_found = true;
      geo_coord.lat.degrees = std::stoi(buffer);
      buffer = "";
    }

    else if(line_to_format[i] == '\'')
    {
      min_found = true;
      geo_coord.lat.minutes = std::stoi(buffer);
      buffer = "";
    }

    else if(line_to_format[i] == '\"')
    {
      sec_found = true;
      geo_coord.lat.seconds = std::stoi(buffer);
      buffer = "";
    }
    
  }

  for(int i=index ; i<line_to_format.size(); i++)
  {
    if(line_to_format[i] == '}')
    {
      index = i+1 ;
      break;
    }

    else if(line_to_format[i] == 176)
    {
      deg_found = true;
      geo_coord.longi.degrees = std::stoi(buffer);
      buffer = "";
    }

    else if(line_to_format[i] == '\'')
    {
      min_found = true;
      geo_coord.longi.minutes = std::stoi(buffer);
      buffer = "";
    }

    else if(line_to_format[i] == '\"')
    {
      sec_found = true;
      geo_coord.longi.seconds = std::stoi(buffer);
      buffer = "";
    }

    else if(isdigit(line_to_format[i]))
    {
      buffer += line_to_format[i];
    }

    else if(isalpha(line_to_format[i]))
    {
      if(line_to_format[i]=='E')
      {
        geo_coord.longi.is_positive=true;
      }

      else if(line_to_format[i]=='W')
      {
        geo_coord.longi.is_positive=false;
      }
    }

    else if(line_to_format[i] == 176)
    {
      deg_found = true;
      geo_coord.longi.degrees = std::stoi(buffer);
      buffer = "";
    }

    else if(line_to_format[i] == '\'')
    {
      min_found = true;
      geo_coord.longi.minutes = std::stoi(buffer);
      buffer = "";
    }

    else if(line_to_format[i] == '\"')
    {
      sec_found = true;
      geo_coord.longi.seconds = std::stoi(buffer);
      buffer = "";
    }
    
  }

  my_coord.cart = {0, 0, 0} ;
  my_coord.geo =  geo_coord;
  result.set_coordinates(my_coord);

  return result;
}

/*
    std::string name;
    std::string buffer = vec[i];
    std::string lat_str;
    std::string longi_str;
    sexagesimal_coordinates lat;
    sexagesimal_coordinates longi;

    bool name_found = false;
    bool lat_found = false;
    bool longi_found = false;
    bool degrees_found = false;
    bool minutes_found = false;
    bool seconds_found = false;
    
    for(int j=0; j<buffer.size(); j++)
    {
      if(buffer[j] == ':')
      {
        name_found = true;
      }

      if(!name_found)
      {
        name += buffer[j];
      }

      else if(name_found && !lat_found)
      {
        if(!isalnum(buffer[j]))
        {
          continue;
        }

        else if(isdigit(buffer[j]) && !degrees_found)
        {
          lat_str += buffer[j];
        }

        else if(buffer[j] == '°')
        {
          std::cout << "lat_str: " << lat_str << std::endl;
          lat.degrees = std::stoi(lat_str);
          std::cout << "lat.degrees: " << lat.degrees << std::endl;
          lat_str = "";
          std::cout << "lat_str: " << lat_str << std::endl;
          degrees_found = true;
        }

        else if(isdigit(buffer[j]) && degrees_found && !minutes_found)
        {
          lat_str += buffer[j];
        }

        else if(buffer[j] == '\'' && buffer[j+1] != '\'')
        {
          lat.minutes = std::stoi(lat_str);
          lat_str = "";
          minutes_found = true;
        }

        else if(isdigit(buffer[j]) && minutes_found && !seconds_found)
        {
          lat_str += buffer[j];
        }

        else if(buffer[j] == '\'' && buffer[j+1] == '\'')
        {
          lat.minutes = std::stoi(lat_str);
          lat_str = "";
          seconds_found = true;
        }

        else if(buffer[j] == 'N' || buffer[j] == 'S')
        {
          lat.seconds = std::stoi(lat_str);
          lat_str = "";
          lat_found = true;

          if(buffer[j] == 'N')
          {
            lat.is_positive = true;
          }

          else
          {
            lat.is_positive = false;
          }
        }

        else if(buffer[j] == '}')
        {
          lat_found = true;
          degrees_found = false;
          minutes_found = false;
          seconds_found = false;
        }

      }

      else if(name_found && lat_found && !longi_found)
      {
        if(!isalnum(buffer[j]))
        {
          continue;
        }

        else if(isdigit(buffer[j]) && !degrees_found)
        {
          longi_str += buffer[j];
        }

        else if(buffer[j] == '°')
        {
          longi.degrees = std::stoi(longi_str);
          longi_str = "";
          degrees_found = true;
        }

        else if(isdigit(buffer[j]) && degrees_found && !minutes_found)
        {
          longi_str += buffer[j];
        }

        else if(buffer[j] == '\'' && buffer[j+1] != '\'')
        {
          longi.minutes = std::stoi(longi_str);
          longi_str = "";
          minutes_found = true;
        }

        else if(isdigit(buffer[j]) && minutes_found && !seconds_found)
        {
          longi_str += buffer[j];
        }

        else if(buffer[j] == '\'' && buffer[j+1] == '\'')
        {
          longi.minutes = std::stoi(longi_str);
          longi_str = "";
          seconds_found = true;
        }

        else if(buffer[j] == 'E' || buffer[j] == 'W')
        {
          longi.seconds = std::stoi(longi_str);
          longi_str = "";
          longi_found = true;

          if(buffer[j] == 'E')
          {
            longi.is_positive = true;
          }

          else
          {
            longi.is_positive = false;
          }
        }

        else if(buffer[j] == '}')
        {
          longi_found = true;
        }
      }
    }
    results[i].set_name(name);
    results[i].set_coordinates(coordinates{geodesic_coordinates{lat, longi}, cartesian_coordinates{0.0, 0.0, 0.0}});
  }
*/