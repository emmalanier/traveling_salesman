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
  for(int i=0; i<destinations.size(); i++)
  {
    std::cout << destinations[i].get_name() << std::endl;
    std::cout << destinations[i].get_coordinates().geo.lat.degrees << "°" << destinations[i].get_coordinates().geo.lat.minutes << "'" << destinations[i].get_coordinates().geo.lat.seconds << "''" << std::endl;
    std::cout << destinations[i].get_coordinates().geo.longi.degrees << "°" << destinations[i].get_coordinates().geo.longi.minutes << "'" << destinations[i].get_coordinates().geo.longi.seconds << "''" << std::endl;
  }
  //Everything above working

  

  return 0;
}