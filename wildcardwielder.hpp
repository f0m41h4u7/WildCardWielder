#pragma once

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

  constexpr char const* file_error = "failed to open file ";
  constexpr char const* rand_device = "/dev/urandom";
  
  constexpr char const* clear_screen = "\x1B[2J\x1B[H";
  
  class WildCardWielder
  {
  public:
    WildCardWielder(std::string& filename, bool is_reverse)
    : m_fname(filename),
      m_is_reverse(is_reverse)
    {}
    ~WildCardWielder() = default;
    
    bool deserialize();
    void serialize();
    
    void run();
    
  private:
    Deck::iterator get_random_card(Deck::iterator, Deck::iterator);
    void shuffle();
    
    std::string m_fname;
	  bool        m_is_reverse{false};
    
    Deck m_to_show;
    Deck m_to_repeat;
    Deck m_whitelist;
    
    std::vector<Card> m_backlog;
  };
  
} //namespace wcw
