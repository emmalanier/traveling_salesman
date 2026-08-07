//SHAPES COORDINATES GENERATION//

#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>

struct vertex
{
    float x, y, z, nx, ny, nz, r, g, b ;
};

std::vector<float> format_sphere_file(std::vector<std::string>&);
std::vector<vertex> compute_sphere_vertices(std::vector<float>&, float&);

#endif//SHAPES_H