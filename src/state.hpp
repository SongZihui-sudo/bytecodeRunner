#ifndef state_hpp
#define state_hpp

#include <string>
#include <map>
#include <unordered_map>

#include "machine.hpp"

struct global_state
{
    std::unordered_map< std::string, std::vector< std::string > > string_table;
    std::map< std::string, unsigned int > var_table;
    std::vector< std::string > code_list;
    std::map< std::string, size_t > label_table;
    machine visual_machine;
};

extern global_state gl_state;

#endif
