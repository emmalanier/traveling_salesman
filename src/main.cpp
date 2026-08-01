//MAIN//

#include "header.h"


int main()
{
  std::string file_name ;
  std::cout << "Please enter the file name: " << std::endl;
  std::cin >> file_name;

  std::vector<std::string> inputs = read_inputs_from_file(file_name);
  std::vector<destination> destinations = format_inputs(inputs);

  //Checkpoint : 
 // for(int i=0; i<destinations.size(); i++)
 // {
 //   std::cout << destinations[i].get_name() << std::endl;
 //   std::cout << destinations[i].get_coordinates().geo.lat.degrees << "°" << destinations[i].get_coordinates().geo.lat.minutes << "'" << destinations[i].get_coordinates().geo.lat.seconds << "''" << std::endl;
 //   std::cout << destinations[i].get_coordinates().geo.longi.degrees << "°" << destinations[i].get_coordinates().geo.longi.minutes << "'" << destinations[i].get_coordinates().geo.longi.seconds << "''" << std::endl;
 // }
  //Everything above working

  for(int i=0; i<destinations.size(); i++)
  {
    destinations[i].convert_to_sec();
    destinations[i].compute_cart_coordinates();

    std::cout << destinations[i].get_name() << " : (" << destinations[i].get_coordinates().cart.x << ", " << destinations[i].get_coordinates().cart.y << ", " << destinations[i].get_coordinates().cart.z << ")" << std::endl;
  }

  //Not sure if convert to sec and compute cart coordinates are working
  double checking_distance = 0.0;
  checking_distance = geodesic_distance_between(destinations[3], destinations[5]);
  std::cout << "Distance between " << destinations[3].get_name() << " and " << destinations[5].get_name() << " is : " << checking_distance << " meters" << std::endl;
  return 0;
}