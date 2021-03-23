#include "wildcardwielder.hpp" 

int main(int argc, char** argv)
{
  try
  {
    if(argc != 2)
    {
      std::cerr << "filename is required as an argument\n";
      return 1;
    }
    std::string fname = argv[1];
    
    wcw::WildCardWielder w{fname};
    if(!w.deserialize()) return 1;
    
    w.run();
  }
  catch(std::exception& ex) { std::cerr << ex.what() << std::endl; }
  
  return 0;
}
