#pragma once

#include <boost/intrusive/list.hpp>
#include <string_view>

namespace wcw
{
  using auto_unlink_hook = boost::intrusive::list_base_hook<boost::intrusive::link_mode<boost::intrusive::auto_unlink>>;
  
  class Card : public auto_unlink_hook
  {
  public:
    Card() = default;
    Card(std::string const& w, std::string const& t)
    : m_word(w),
      m_translate(t)
    {}
    
    ~Card() = default;
    
    std::string_view word() const noexcept { return m_word; }
    std::string_view translate() const noexcept { return m_translate; }
    
    void word(std::string_view w) { m_word = w.data(); }
    void translate(std::string_view t) { m_translate = t.data(); }
    
    void unlink_from_deck() noexcept { auto_unlink_hook::unlink(); }
    bool is_linked() const noexcept { return auto_unlink_hook::is_linked(); }
    
  private:
    std::string m_word;
    std::string m_translate;
  };
  
  using Deck = boost::intrusive::list<Card, boost::intrusive::constant_time_size<false>>;
  
} //namespace wcw
