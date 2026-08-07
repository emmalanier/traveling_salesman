//SHAPES//

#include "header.h"
#include "shapes.h"

std::vector<float> format_sphere_file(std::vector<std::string>& vec)
{
   std::vector<float> results;
   float x;
   float y;
   float z;

   std::string x_str;
   std::string y_str;
   std::string z_str;

   bool got_x;
   bool got_y;

   for(int i=0; vec.size(); i++)
   {
     if(i!=0)
     {
        x = stof(x_str);
        y = stof(y_str);
        z = stof(z_str);
        results.push_back(x);
        results.push_back(y);
        results.push_back(z);
     }

     got_x = false;
     got_y = false;
     x_str.clear();
     y_str.clear();
     z_str.clear();
     
        for(int j=0; j<vec[i].length(); j++)
        {
            if(vec[i][j]=='\n' && !got_x)
            {
                got_x = true;
            }
            else if(vec[i][j]=='\n' && got_x)
            {
                got_y = true;
            }

            else if(!got_x)
            {
                x_str+=vec[i][j];
            }

            else if(!got_y)
            {
                y_str+=vec[i][j];
            }

            else
            {
                z_str+=vec[i][j];
            }
        }
   }
   
   return results ;
}

std::vector<vertex> compute_sphere_vertices(std::vector<float>& vec)
{
    std::vector<vertex> results;
    vertex point;

    float x_var;
    float y_var;
    float z_var;

    for(int i=0; i<vec.size(); i++)
    {

    }

    return results;
}