#include <boost/program_options.hpp>

#include "wildcardwielder.hpp"

namespace po = boost::program_options;

int main()
{
  try
  {
	po::options_description desc("WildCardWielder - tool for learning words. Usage:");
	desc.add_options()
	  ("help", "produce help message")
	  ("f", po::value<std::string>(), "provide path to file with cards")
	  ("r", "set reverse mode")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);
	po::notify(vm);    

	if (vm.count("help"))
	{
	  std::cout << desc << "\n";
	  return 1;
	}

	std::string fname;
	if (vm.count("f"))
	  fname = vm["compression"].as<std::string>();
	else
	{
	  std::cerr << "filename is required as an argument\n";
	  return 1;
	}
	
	bool is_reverse = false;
	if (vm.count("f"))
		is_reverse = true;
    
    wcw::WildCardWielder w{fname, is_reverse};
    if(!w.deserialize()) return 1;
    
    w.run();
  }
  catch(std::exception& ex) { std::cerr << ex.what() << std::endl; }
  
  return 0;
}
