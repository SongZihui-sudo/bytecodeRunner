#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <iomanip>
#include <array>

#include "machine.hpp"
#include "instruction.hpp"

machine visual_machine;

#define current_code_stream code_list

#define is_Comment( code ) if ( code[0] == '#' )

/**
 * @brief repl
 *
 */
void repl( std::vector< std::vector< token > > tokens )
{
    std::vector< token > line;
    while ( visual_machine.get_register( "PC" ) < tokens.size() )
    {
        line         = tokens[visual_machine.get_register( "PC" )];
        size_t index = 0;
        visual_machine.set_register( "PC", visual_machine.get_register( "PC" ) + 1 );
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
                cur_token.type  = NUMBER;
                cur_token.value = std::stoul( tmp );
                cur_token.name  = tmp;
            }
            else if ( visual_machine.is_register( tmp ) )
            {
                cur_token.type  = REGISTER;
                cur_token.value = visual_machine.get_register( tmp );
                cur_token.name  = tmp;
            }
            else if ( cur.back() == ':' )
            {
                token cur_token;
                cur_token.type                               = LABEL;
                cur_token.value                              = tmp_index;
                cur_token.name                               = cur;
                label_table[cur.substr( 0, cur.size() - 1 )] = tmp_index;
                if ( cur == "main():" )
                {
                    visual_machine.set_register( "PC", tmp_index + 1 );
                };
            }
            else if ( tmp[0] == '[' )
            {
                std::string tmp_str = tmp.substr( 1, tmp.size() - 2 );
                if ( isNumber( tmp_str ) )
                {
                    cur_token.type  = MEMORY;
                    cur_token.value = visual_machine.get_memory( std::stoul( tmp_str ) );
                    cur_token.name  = tmp;
                }
                else if ( visual_machine.is_register( tmp_str ) )
                {
                    cur_token.type  = REGISTER_INDIRECT;
                    cur_token.value = 0;
                    tmp.pop_back();
                    tmp.erase( tmp.begin() );
                    cur_token.name = tmp;
                }
                else if ( var_table.count( tmp_str ) )
                {
                    cur_token.type  = MEMORY;
                    cur_token.value = var_table[tmp_str];
                    cur_token.name  = tmp;
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
                    cur_token.type  = OPER;
                    cur_token.value = 0;
                    cur_token.name  = tmp;
                }
                else
                {
                    if ( !pos )
                    {
                        DEBUG_INFO( "Opcode error: " << tmp );
                        exit( 0 );
                    }
                    cur_token.type  = VAR;
                    cur_token.value = 0;
                    cur_token.name  = tmp;
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
