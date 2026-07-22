//HEADER FILE//

#ifndef HEADER_H
#define HEADER_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <vector>

class destination
{
  private :
    double m_lat;
    double m_long;
    double m_alt;
    std::string m_name;

  public :
    double get_lat();
    double get_long();
    double get_alt();
    std::string get_name();

    void set_lat(const double&);
    void set_long(const double&);
    void set_alt(const double&);
    void set_name(const std::string&);
};

#endif //HEADER_H