//HEADER FILE//

#ifndef HEADER_H
#define HEADER_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

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

    coordinates get_coordinates();
    double get_alt();
    std::string get_name();

    void set_coordinates(const coordinates&);
    void set_alt(const double&);
    void set_name(const std::string&);

    void compute_cart_coordinates();
    void convert_to_sec();

    bool operator<(const destination& other) const
    {
      return m_name < other.m_name;
    }
};

double cart_distance_between(destination&, destination&);
double geodesic_distance_between(destination&, destination&);

//Two methods will be implemented, and compared
std::vector<destination> optimised_route_1(std::vector<destination>&, destination&);
std::vector<destination> optimised_route_2(std::vector<destination>&, destination&);

//Inputs reading
std::vector<std::string> read_inputs_from_file(const std::string&);

//Inputs formatting
std::vector<destination> format_inputs(std::vector<std::string>&);
void rm_start(std::vector<destination>&, destination&);
int get_start_index(std::vector<destination>&, destination&);

//Math
int factorial(int);
void permutate(std::vector<destination>&, int, int);
#endif //HEADER_H