//MAIN//

#include "header.h"


int main()
{
  std::string file_name ;
  std::cout << "Please enter the file name: " << std::endl;
  std::cin >> file_name;

  std::vector<std::string> inputs = read_inputs_from_file(file_name);
  std::vector<destination> destinations = format_inputs(inputs);

  for(int i=0; i<destinations.size(); i++)
  {
    destinations[i].convert_to_sec();
    destinations[i].compute_cart_coordinates();
  }

  //Not sure if convert to sec and compute cart coordinates are working
  double checking_distance = 0.0;
  checking_distance = geodesic_distance_between(destinations[0], destinations[3]);
  std::cout << "Distance between " << destinations[0].get_name() << " and " << destinations[3].get_name() << " is : " << checking_distance << " meters" << std::endl;
  return 0;
}