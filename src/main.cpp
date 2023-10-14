#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <iomanip>
#include <array>

#include "state.hpp"
#include "instruction.hpp"

#define current_code_stream visual_machine.code_list

#define is_Comment( code ) if ( code[0] == '#' )

machine visual_machine;

/**
 * @brief repl
 *
 */
void repl( std::vector< std::vector< token > > tokens )
{
    std::vector< token > line;
    while ( visual_machine.visual_machine_state.get_register( "PC" )
            < UINT_VALUE( ( unsigned int )tokens.size() ) )
    {
        line
        = tokens[GET_UINT_VALUE( visual_machine.visual_machine_state.get_register( "P"
                                                                                   "C" ) )];
        size_t index = 0;
        visual_machine.visual_machine_state.set_register(
        "PC", visual_machine.visual_machine_state.get_register( "PC" ) + INT_VALUE( 1 ) );
        visual_machine.visual_instruction_runner.do_instruction( line );
    }
}

/**
 * @brief preprocess
 *
 */
std::vector< std::vector< token > > preprocess()
{
    std::vector< std::vector< token > > tokens;
    size_t tmp_index = 0;
    for ( auto cur : current_code_stream )
    {
        std::vector< token > line_tokens;
        std::stringstream ss( cur );
        std::string tmp;
        size_t pos = 0;
        while ( ss >> tmp )
        {
            token cur_token;
            is_Comment( tmp ) { continue; }
            else if ( isNumber( tmp ) )
            {
                cur_token = { tmp, UINT_VALUE( std::stoul( tmp ) ), NUMBER };
            }
            else if ( visual_machine.visual_machine_state.is_register( tmp ) )
            {
                cur_token = { tmp, UINT_VALUE( 0 ), REGISTER };
            }
            else if ( cur.back() == ':' )
            {
                cur_token = { cur, UINT_VALUE( tmp_index ), LABEL };
                visual_machine.label_table[cur.substr( 0, cur.size() - 1 )] = tmp_index;
                if ( cur == "main():" )
                {
                    visual_machine.visual_machine_state.set_register( "PC",
                                                                      UINT_VALUE( tmp_index )
                                                                      + UINT_VALUE( 1 ) );
                };
            }
            else if ( tmp[0] == '[' )
            {
                std::string tmp_str = tmp.substr( 1, tmp.size() - 2 );
                if ( isNumber( tmp_str ) )
                {
                    cur_token
                    = { tmp, visual_machine.visual_machine_state.get_memory( std::stoul( tmp_str ) ), MEMORY };
                }
                else if ( visual_machine.visual_machine_state.is_register( tmp_str ) )
                {
                    tmp.pop_back();
                    tmp.erase( tmp.begin() );
                    cur_token = { tmp, UINT_VALUE( 0 ), EXPRESSION };
                }
                else
                {
                    DEBUG_INFO( "The memory address should be a number or a register!" );
                    exit( -1 );
                }
            }
            else
            {
                std::transform( tmp.begin(), tmp.end(), tmp.begin(), ::toupper );
                if ( visual_machine.visual_instruction_runner.do_instruction_funcs.count( tmp ) )

                {
                    cur_token = { tmp, UINT_VALUE( 0 ), OPER };
                }
                else
                {
                    if ( !pos )
                    {
                        DEBUG_INFO( "Opcode error: " << tmp );
                        exit( -1 );
                    }
                    cur_token = { tmp, UINT_VALUE( 0 ), VAR };
                }
            }
            line_tokens.push_back( cur_token );
            pos++;
        }
        tokens.push_back( line_tokens );
        tmp_index++;
    }
    return tokens;
}

int main( int argc, char** argv )
{
    visual_machine.visual_instruction_runner.load_file( "./example.asm" );
    std::vector< std::vector< token > > tokens = preprocess();
    repl( tokens );
    return 0;
}
