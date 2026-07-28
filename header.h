//HEADER FILE//

#ifndef HEADER_H
#define HEADER_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <vector>

#define EARTH_RADIUS 6.370e06
#define MINUTE 1.00/60.0
#define SECOND 1.00/3600.0

struct sexagesimal_coordinates
{
  bool is_positive;
  int degrees;
  int minutes;
  int seconds;
  int total_sec;
};

struct geodesic_coordinates
{
  sexagesimal_coordinates lat;
  sexagesimal_coordinates longi;
};

struct cartesian_coordinates
{
  double x;
  double y;
  double z;
};

struct coordinates
{
  geodesic_coordinates geo;
  cartesian_coordinates cart;
};

class destination
{
  private :
    coordinates m_coordinates;
    double m_alt;
    std::string m_name;

  public :
    destination();
    destination(coordinates, double, std::string);

    coordinate get_lat();
    coordinate get_long();
    double get_alt();
    std::string get_name();

    void set_lat(const coordinate&);
    void set_long(const coordinate&);
    void set_alt(const double&);
    void set_name(const std::string&);

    //double cartesian_distance_to(destination&);
    double geodesic_distance_to(destination&);

    void compute_cart_coordinates();
    void convert_to_sec();
};

double cart_distance_between(const destination&, const destination&);

#endif //HEADER_H