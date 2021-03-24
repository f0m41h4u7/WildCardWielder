#pragma once

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>
#include <vector>

#include "card.hpp"

namespace wcw
{
  constexpr char const delimiter = '-';
  constexpr char const newline = '\n';
  constexpr char const* lists_separator = "===";
  constexpr char const* wrong_response = "you are a stupid idiot! correct is: ";
  constexpr char const* right_response = "rrright!\n";
  
  constexpr std::size_t cards_qty = 10;
  
  class WildCardWielder
  {
  public:
    WildCardWielder(std::string& filename, bool is_reverse)
    : m_fname(filename),
      m_is_reverse(is_reverse)
    {}
    ~WildCardWielder() = default;
    
    bool deserialize()
    {
      std::ifstream file(m_fname);
      if(!file)
      {
        std::cerr << "failed to open file " << m_fname << std::endl;
        return 0;
      }
      
      std::string line, word, translate;
      std::size_t pos;
      std::size_t wl = 0;
      while(std::getline(file, line))
      {
        if (!line.empty())
        {
          if(line == lists_separator)
            wl = m_backlog.size();
            
          if((pos = line.find(delimiter)) != std::string::npos)
            m_backlog.emplace_back(line.substr(0, pos), line.substr(pos+1, line.size()));
        }
      }
      file.close();
      
      assert(m_backlog.size() >= cards_qty);
      
      for(std::size_t i = 0; i < wl; ++i)
        m_whitelist.push_back(m_backlog[i]);
      for(std::size_t i = wl; i < m_backlog.size(); ++i)
        m_to_repeat.push_back(m_backlog[i]);
      
      return 1;
    }
    
    void serialize()
    {
      std::ofstream file(m_fname);
      if(!file)
      {
        std::cerr << "failed to open file " << m_fname << std::endl;
        return;
      }
      
      for(auto const& c : m_whitelist)
        file << c.word() << delimiter << c.translate() << newline;
      file << lists_separator << newline;
      
      for(auto const& c : m_to_repeat)
        file << c.word() << delimiter << c.translate() << newline;
      
      file.close();
    }

    void run()
    {
      shuffle();
      
      std::string res, check;
      Deck::iterator it;
      
      for(std::size_t i = 0; i < cards_qty; ++i)
      {
        it = get_random_card(m_to_show.begin(), m_to_show.end());
		
        if(m_is_reverse)
        {
          std::cout << (*it).translate() << std::endl;
          check = (*it).word();
        }
        else
        {
          std::cout << (*it).word() << std::endl;
          check = (*it).translate();
        }
		
        std::getline(std::cin, res);
        if(res != check)
        {
          std::cout << wrong_response << check << newline;
          (*it).unlink_from_deck();
          m_to_repeat.push_back(*it);
        }
        else 
        {
          std::cout << right_response;
          (*it).unlink_from_deck();
          m_whitelist.push_back(*it);
        }
      }
      
      serialize();
    }
    
  private:
    Deck::iterator get_random_card(Deck::iterator start, Deck::iterator end)
    {
      static std::random_device rd("/dev/urandom");
      static std::mt19937 gen(rd());
      std::uniform_int_distribution<int> dist(0, std::distance(start, end) - 1);
      std::advance(start, dist(gen));
      return start;
    }
    
    void shuffle()
    {
      Deck::iterator it;
      m_to_show.clear();
      auto r = 3*cards_qty/4;
      
      for(std::size_t i = 0; i < r; ++i)
      {
        it = get_random_card(m_to_repeat.begin(), m_to_repeat.end());
        (*it).unlink_from_deck();
        m_to_show.push_back(*it);
      }
      
      for(std::size_t i = 0; i < cards_qty-r; ++i)
      {
        it = get_random_card(m_whitelist.begin(), m_whitelist.end());
        (*it).unlink_from_deck();
        m_to_show.push_back(*it);
      }
    }
    
    std::string m_fname;
	  bool        m_is_reverse{false};
    
    Deck m_to_show;
    Deck m_to_repeat;
    Deck m_whitelist;
    
    std::vector<Card> m_backlog;
  };
  
} //namespace wcw
