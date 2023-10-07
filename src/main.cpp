#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <iomanip>
#include <array>

#include "state.hpp"
#include "instruction.hpp"

#define current_code_stream gl_state.code_list

#define is_Comment( code ) if ( code[0] == '#' )

global_state gl_state;

/**
 * @brief repl
 *
 */
void repl( std::vector< std::vector< token > > tokens )
{
    std::vector< token > line;
    while ( gl_state.visual_machine.get_register( "PC" ) < tokens.size() )
    {
        line         = tokens[gl_state.visual_machine.get_register( "PC" )];
        size_t index = 0;
        gl_state.visual_machine.set_register( "PC", gl_state.visual_machine.get_register( "PC" ) + 1 );
        do_instruction( line );
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
                cur_token = { tmp, std::stoul( tmp ), NUMBER };
            }
            else if ( gl_state.visual_machine.is_register( tmp ) )
            {
                cur_token = { tmp, 0, REGISTER };
            }
            else if ( cur.back() == ':' )
            {
                cur_token = { cur, ( unsigned int )tmp_index, LABEL };
                gl_state.label_table[cur.substr( 0, cur.size() - 1 )] = tmp_index;
                if ( cur == "main():" )
                {
                    gl_state.visual_machine.set_register( "PC", tmp_index + 1 );
                };
            }
            else if ( tmp[0] == '[' )
            {
                std::string tmp_str = tmp.substr( 1, tmp.size() - 2 );
                if ( isNumber( tmp_str ) )
                {
                    cur_token
                    = { tmp, gl_state.visual_machine.get_memory( std::stoul( tmp_str ) ), MEMORY };
                }
                else if ( gl_state.visual_machine.is_register( tmp_str ) )
                {
                    tmp.pop_back();
                    tmp.erase( tmp.begin() );
                    cur_token = { tmp, 0, REGISTER_INDIRECT };
                }
                else
                {
                    DEBUG_INFO( "The memory address should be a number or a register!" );
                    return {};
                }
            }
            else
            {
                std::transform( tmp.begin(), tmp.end(), tmp.begin(), ::toupper );
                if ( do_instruction_func.count( tmp ) )

                {
                    cur_token = { tmp, 0, OPER };
                }
                else
                {
                    if ( !pos )
                    {
                        DEBUG_INFO( "Opcode error: " << tmp );
                        exit( 0 );
                    }
                    cur_token = { tmp, 0, VAR };
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
    load_file( "./example.asm" );
    std::vector< std::vector< token > > tokens = preprocess();
    repl( tokens );
    return 0;
}
