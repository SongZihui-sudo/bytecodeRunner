#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <iomanip>

#include "machine.hpp"
#include "instruction.hpp"

machine visual_machine;

static std::vector< std::string > asm_code_test1
= { "mov 99 eax", "mov eax ebx", "mov eax [0]", "mov 101 [1]",
    "pr ebx",     "pr eax",      "pm 0 100" };
static std::vector< std::string > asm_code_test2
= { "add 100 99", "pr acc", "sub 100 3",   "pr acc",
    "mul 98 97",  "pr mq",  "div 99 3000", "pr mq" };
static std::vector< std::string > asm_code_test3
= { "push 99", "pop r8", "pr r8", "pr ebp", "ps" };
static std::vector< std::string > asm_code_test4 = { "jmp 2", "add 1 2", "pr acc" };
static std::vector< std::string > asm_code_test5
= { "cmp 1 1", "je 3", "add 1 1", "pr acc" };
static std::vector< std::string > asm_code_test6
= { "jmp test_label", "add 1 2", "test_label:", "pr acc", "# test code 6" };
static std::vector< std::string > asm_code_test7
= { "test_func():", "push ebp", "mov ebp esp", "add 1 1",          "pr acc", "ret",
    "main():",      "push ebp", "mov ebp esp", "call test_func()", "leave",  "ret" };

#define current_code_stream asm_code_test1

/**
 * @brief repl
 *
 */
void repl()
{
    std::string line;
    while ( visual_machine.get_PC() < current_code_stream.size() )
    {
        line            = current_code_stream[visual_machine.get_PC()];
        size_t index    = 0;
        std::string tmp = line.substr( index, line.find( ' ' ) );
        visual_machine.set_PC( visual_machine.get_PC() + 1 );
        if ( line == "help" )
        {
            std::cout << "help: print help message" << std::endl;
            std::cout << "exit: exit the program" << std::endl;
            std::cout << "pr [register name]: print register" << std::endl;
            std::cout << "pm [start index] [read size]: print memory" << std::endl;
        }
        else if ( line == "exit" || line == "leave" )
        {
            break;
        }
        else if ( tmp == "pr" )
        {
            line.erase( 0, 3 );
            tmp = line.substr( index, line.find( ' ' ) );
            visual_machine.print_reg( tmp );
        }
        else if ( tmp == "pm" )
        {
            tmp.clear();
            line.erase( 0, 3 );
            unsigned int space = line.find( ' ' );
            tmp                = line.substr( index, space );
            index              = space + 1;
            if ( !isNumber( tmp ) )
            {
                DEBUG_INFO( "Parameter should be immediate!" );
            }
            unsigned int start = std::stoul( tmp );
            line.erase( 0, index );
            if ( !isNumber( line ) )
            {
                DEBUG_INFO( "Parameter should be immediate!" );
            }
            unsigned int read_size = std::stoul( line );
            visual_machine.print_memory( start, read_size );
        }
        else if ( tmp == "p" )
        {
            tmp.clear();
            line.erase( 0, 2 );
            std::cout << line << std::endl;
        }
        else if ( tmp == "ps" )
        {
            visual_machine.print_stack();
        }
        else
        {
            do_instruction( line );
        }
    }
}

/**
 * @brief preprocess
 *
 */
void preprocess()
{
    size_t tmp_index = 0;
    for ( auto cur : current_code_stream )
    {
        if ( cur == "main():" )
        {
            label_table[cur] = tmp_index;
            current_code_stream.erase( current_code_stream.begin() + tmp_index );
            visual_machine.set_PC( tmp_index );
        }
        else if ( cur.back() == ':' )
        {
            cur.pop_back();
            label_table[cur] = tmp_index;
            current_code_stream.erase( current_code_stream.begin() + tmp_index );
        }
        else if ( cur.front() == '#' )
        {
            current_code_stream.erase( current_code_stream.begin() + tmp_index );
        }
        tmp_index++;
    }
}

int main( int argc, char** argv )
{
    preprocess();
    repl();
    return 0;
}
