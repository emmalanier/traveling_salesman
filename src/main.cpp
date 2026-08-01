//MAIN//

#include "header.h"


int main()
{
  std::string file_name ;
  std::cout << "Please enter the file name: " << std::endl;
  std::cin >> file_name;

  std::vector<std::string> inputs = read_inputs_from_file(file_name);
  std::vector<destination> destinations = format_inputs(inputs);

  std::vector<destination> opt_route_1;
  std::vector<destination> opt_route_2;

  for(int i=0; i<destinations.size(); i++)
  {
    destinations[i].convert_to_sec();
    destinations[i].compute_cart_coordinates();
  }

  std::cout << "Let's optimize" << std::endl;
  
  std::cout << "Optimizing the route using method 1..." << std::endl;
  opt_route_1 = optimised_route_1(destinations, destinations[0]);
  std::cout << "Route optimized using method 1 done. Results : " << std::endl;
  for(int i=0; i<opt_route_1.size(); i++)
  {
    std::cout << i << ". " << opt_route_1[i].get_name() << std::endl;
  }

  std::cout << "Optimizing the route using method 2... (this might take time)" << std::endl;
  opt_route_2 = optimised_route_2(destinations, destinations[0]);
  std::cout << "Route optimized using method 2 done. Results : " << std::endl;
  for(int i=0; i<opt_route_2.size(); i++)
  {
    std::cout << i << ". " << opt_route_2[i].get_name() << std::endl;
  }


  return 0;
}