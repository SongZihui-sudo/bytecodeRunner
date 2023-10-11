#ifndef state_hpp
#define state_hpp

#include <string>
#include <map>
#include <unordered_map>

#include "machine.hpp"
#include "instruction.hpp"

struct machine
{
    std::unordered_map< std::string, std::vector< std::string > > string_table;
    std::map< std::string, unsigned int > var_table;
    std::vector< std::string > code_list;
    std::map< std::string, size_t > label_table;
    machine_state visual_machine_state;
    instruction_runner visual_instruction_runner;
};

extern machine visual_machine;

#endif
