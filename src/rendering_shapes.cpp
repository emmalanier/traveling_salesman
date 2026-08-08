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

std::vector<vertex> compute_sphere_vertices(std::vector<float>& vec, float& radius)
{
    std::vector<vertex> results;
    vertex point;

    float x_var;
    float y_var;
    float z_var;

    point.r = 0.75f;
    point.g = 0.75f;
    point.b = 1.0f;

    for(int i=0; i<vec.size()/3; i++)
    {
        x_var=vec[3*i];
        y_var=vec[1+3*i];
        z_var=vec[2+3*i];
        
        point.x = x_var;
        point.y = y_var;
        point.z = z_var;

        point.nx = 1.0f*(x_var/radius);
        point.ny = 1.0f*(y_var/radius);
        point.nz = 1.0f*(z_var/radius);

        results.push_back(point);
    }

    return results;
}

std::vector<int> compute_indices(std::vector<vertex>& vec, int& n_lat, int& n_long)
{
    //n_lat is the number of latitude lines, n_long the number of ongitude lines
    //For the latitude, the poles are counted
    std::vector<int> results;

    int sq_tl;
    int sq_tr;
    int sq_bl;
    int sq_br;

    int upper_lat;
    int lower_lat;

    //int first_long;

    int left_long;
    int right_long;

    int indice_1=0;
    int indice_2;
    int indice_3;

    //First row
    for(int i=1; i<=n_long; i++)
    {
        indice_2 = 2*i;
        indice_3 = 1 + 2*i;

        results.push_back(indice_1);
        results.push_back(indice_2);
        results.push_back(indice_3);
    }

    //Middle rows
    for(int i=1; i<n_lat; i++)
    {
        upper_lat=i;
        lower_lat=i+1;

        for(int j=0; j<n_long; j++)
        {
            left_long=j;
            right_long=j+1;

            sq_tl=upper_lat+left_long;
            sq_tr=upper_lat+right_long;
            sq_bl=lower_lat+left_long;
            sq_br=lower_lat+right_long;

            indice_1=sq_tl;
            indice_2=sq_bl;
            indice_3=sq_br;

            results.push_back(indice_1);
            results.push_back(indice_2);
            results.push_back(indice_3);

            indice_1=sq_tl;
            indice_2=sq_tr;
            indice_3=sq_bl;

            results.push_back(indice_1);
            results.push_back(indice_2);
            results.push_back(indice_3);
        }
    }

    indice_1= 1 + n_lat*n_long;
    //Last row
    for(int i=1; i<=n_long; i++)
    {
        indice_2 = (n_lat-1)*i;
        indice_3 = 1+(n_lat-1)*i;

        results.push_back(indice_1);
        results.push_back(indice_2);
        results.push_back(indice_3);
    }
}