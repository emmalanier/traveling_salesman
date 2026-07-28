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

struct coordinate
{
  double degrees;
  double minutes;
  double seconds;
};

class destination
{
  private :
    coordinate m_lat;
    coordinate m_long;
    double m_alt;
    std::string m_name;

  public :
    destination();
    destination(coordinate, coordinate, double, std::string);

    coordinate get_lat();
    coordinate get_long();
    double get_alt();
    std::string get_name();

    void set_lat(const coordinate&);
    void set_long(const coordinate&);
    void set_alt(const double&);
    void set_name(const std::string&);

    double geodesic_distance_to(destination&);
};

#endif //HEADER_H