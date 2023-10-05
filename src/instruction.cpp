#include "instruction.hpp"
#include "machine.hpp"

#include <sstream>
#include <fstream>
#include <array>

std::unordered_map< std::string, unsigned int > var_table;

std::unordered_map< std::string, size_t > label_table;

std::vector< std::string > code_list;

const std::unordered_map< std::string, std::function< void( token, token ) > > do_instruction_func
= { { "HELP",
      []( token arg1, token arg2 )
      {
          std::cout << "help: print help message" << std::endl;
          std::cout << "exit: exit the program" << std::endl;
          std::cout << "pr [register name]: print register" << std::endl;
          std::cout << "pm [start index] [read size]: print memory" << std::endl;
      } },
    { "EXIT", []( token arg1, token arg2 ) { exit( 0 ); } },
    { "LEAVE", []( token arg1, token arg2 ) { exit( 0 ); } },
    { "PR", []( token arg1, token arg2 ) { visual_machine.print_reg( arg1.name ); } },
    { "PM",
      []( token arg1, token arg2 )
      {
          std::cout << "Please input the start index: ";
          unsigned int start;
          std::cin >> start;
          std::cout << "Please input the read size: ";
          unsigned int read_size;
          std::cin >> read_size;
          visual_machine.print_memory( start, read_size );
      } },
    { "PS", []( token arg1, token arg2 ) { visual_machine.print_stack(); } },
    { "MOV", do_mov },
    { "ADD", do_add },
    { "SUB", do_sub },
    { "MUL", do_mul },
    { "DIV", do_div },
    { "PUSH", do_push },
    { "POP", do_pop },
    { "JMP", do_jmp },
    { "CMP", do_cmp },
    { "JE", do_je },
    { "JNE", do_jne },
    { "JBE", do_jbe },
    { "JA", do_ja },
    { "JB", do_jb },
    { "JNB", do_jnb },
    { "CALL", do_call },
    { "RET", do_ret } };

bool isNumber( const std::string& str )
{
    for ( char const& c : str )
    {
        if ( std::isdigit( c ) == 0 )
            return false;
    }
    return true;
}

bool do_instruction( std::vector< token > line )
{

    line.push_back( token() );
    if ( do_instruction_func.count( line[0].name ) )
    {
        do_instruction_func.at( line[0].name )( line[1], line[2] );
        return true;
    }
    return true;
}

void do_mov( token dist, token source )
{
    if ( dist.type == NUMBER )
    {
        DEBUG_INFO( "The destination should not be a number!" );
    }
    else
    {
        unsigned int tmp = source.value;
        if ( source.type == MEMORY )
        {
            tmp = visual_machine.get_memory( tmp );
        }
        if ( dist.type == REGISTER )
        {
            visual_machine.set_register( dist.name, tmp );
        }
        else if ( dist.type == VAR )
        {
            var_table[dist.name] = tmp;
        }
        else if ( dist.type == MEMORY )
        {
            visual_machine.set_memory( dist.value, tmp );
        }
        else
        {
            DEBUG_INFO( "The destination should be a register or a variable!" );
        }
    }
}

void do_add( token dist, token source )
{
    unsigned int tmp1 = dist.value;
    unsigned int tmp2 = source.value;
    if ( dist.type == MEMORY )
    {
        tmp1 = visual_machine.get_memory( tmp1 );
    }
    else if ( dist.type == REGISTER )
    {
        tmp1 = visual_machine.get_register( dist.name );
    }
    else if ( dist.type == VAR )
    {
        tmp1 = var_table[dist.name];
    }
    if ( source.type == MEMORY )
    {
        tmp2 = visual_machine.get_memory( tmp2 );
    }
    else if ( source.type == REGISTER )
    {
        tmp2 = visual_machine.get_register( source.name );
    }
    else if ( source.type == VAR )
    {
        tmp2 = var_table[source.name];
    }
    visual_machine.set_register( "ACC", tmp1 + tmp2 );
}

void do_sub( token dist, token source )
{
    unsigned int tmp1 = dist.value;
    unsigned int tmp2 = source.value;
    if ( dist.type == MEMORY )
    {
        tmp1 = visual_machine.get_memory( tmp1 );
    }
    else if ( dist.type == REGISTER )
    {
        tmp1 = visual_machine.get_register( dist.name );
    }
    else if ( dist.type == VAR )
    {
        tmp1 = var_table[dist.name];
    }
    if ( source.type == MEMORY )
    {
        tmp2 = visual_machine.get_memory( tmp2 );
    }
    else if ( source.type == REGISTER )
    {
        tmp2 = visual_machine.get_register( source.name );
    }
    else if ( source.type == VAR )
    {
        tmp2 = var_table[source.name];
    }
    visual_machine.set_register( "ACC", tmp1 - tmp2 );
}

void do_div( token dist, token source )
{
    unsigned int tmp1 = dist.value;
    unsigned int tmp2 = source.value;
    if ( dist.type == MEMORY )
    {
        tmp1 = visual_machine.get_memory( tmp1 );
    }
    else if ( dist.type == REGISTER )
    {
        tmp1 = visual_machine.get_register( dist.name );
    }
    else if ( dist.type == VAR )
    {
        tmp1 = var_table[dist.name];
    }
    if ( source.type == MEMORY )
    {
        tmp2 = visual_machine.get_memory( tmp2 );
    }
    else if ( source.type == REGISTER )
    {
        tmp2 = visual_machine.get_register( source.name );
    }
    else if ( source.type == VAR )
    {
        tmp2 = var_table[source.name];
    }
    visual_machine.set_register( "MQ", tmp1 / tmp2 );
}

void do_mul( token dist, token source )
{
    unsigned int tmp1 = dist.value;
    unsigned int tmp2 = source.value;
    if ( dist.type == MEMORY )
    {
        tmp1 = visual_machine.get_memory( tmp1 );
    }
    else if ( dist.type == REGISTER )
    {
        tmp1 = visual_machine.get_register( dist.name );
    }
    else if ( dist.type == VAR )
    {
        tmp1 = var_table[dist.name];
    }
    if ( source.type == MEMORY )
    {
        tmp2 = visual_machine.get_memory( tmp2 );
    }
    else if ( source.type == REGISTER )
    {
        tmp2 = visual_machine.get_register( source.name );
    }
    else if ( source.type == VAR )
    {
        tmp2 = var_table[source.name];
    }
    visual_machine.set_register( "MQ", tmp1 * tmp2 );
}

void do_push( token dist, token source )
{
    if ( dist.type == NUMBER )
    {
        visual_machine.push( dist.value );
    }
    else if ( dist.type == REGISTER )
    {
        visual_machine.push( visual_machine.get_register( dist.name ) );
    }
    else if ( dist.type == VAR )
    {
        visual_machine.push( var_table[dist.name] );
    }
    else if ( dist.type == MEMORY )
    {
        visual_machine.push( visual_machine.get_memory( dist.value ) );
    }
    else
    {
        DEBUG_INFO( "The dist should be a number or a register or a variable!" );
    }
}

void do_pop( token dist, token source )
{
    if ( dist.type == NUMBER )
    {
        DEBUG_INFO( "The destination should not be a number!" );
    }
    else
    {
        unsigned int tmp = visual_machine.top();
        if ( dist.type == REGISTER )
        {
            visual_machine.set_register( dist.name, tmp );
        }
        else if ( dist.type == VAR )
        {
            var_table[dist.name] = tmp;
        }
        else if ( dist.type == MEMORY )
        {
            visual_machine.set_memory( dist.value, tmp );
        }
        else
        {
            DEBUG_INFO( "The destination should be a register or a variable!" );
        }
    }
    visual_machine.pop();
}

void do_jmp( token dist, token source )
{
    if ( dist.type == MEMORY )
    {
        visual_machine.set_register( "PC", visual_machine.get_memory( dist.value ) );
    }
    else if ( dist.type == LABEL || dist.type == NUMBER || dist.type == VAR || dist.type == REGISTER )
    {
        visual_machine.set_register( "PC", dist.value );
    }
    else
    {
        DEBUG_INFO( "The destination should be a number or a variable!" );
    }
}

void do_cmp( token dist, token source )
{
    if ( dist.type == NUMBER )
    {
        visual_machine.set_register( "ZF", dist.value == source.value );
        visual_machine.set_register( "SF", dist.value < source.value );
    }
    else if ( dist.type == REGISTER )
    {
        visual_machine.set_register( "ZF",
                                     visual_machine.get_register( dist.name ) == source.value );
        visual_machine.set_register( "SF", visual_machine.get_register( dist.name ) < source.value );
    }
    else if ( dist.type == VAR )
    {
        visual_machine.set_register( "ZF", var_table[dist.name] == source.value );
        visual_machine.set_register( "SF", var_table[dist.name] < source.value );
    }
    else if ( dist.type == MEMORY )
    {
        visual_machine.set_register( "ZF", visual_machine.get_memory( dist.value ) == source.value );
        visual_machine.set_register( "SF", visual_machine.get_memory( dist.value ) < source.value );
    }
    else
    {
        DEBUG_INFO( "The destination should be a number or a register or a variable!" );
    }
}

void do_je( token dist, token source )
{
    if ( visual_machine.get_register( "ZF" ) )
    {
        do_jmp( dist, source );
    }
}

void do_jne( token dist, token source )
{
    if ( !visual_machine.get_register( "ZF" ) )
    {
        do_jmp( dist, source );
    }
}

void do_jbe( token dist, token source )
{
    if ( visual_machine.get_register( "ZF" ) || visual_machine.get_register( "SF" ) )
    {
        do_jmp( dist, source );
    }
}

void do_ja( token dist, token source )
{
    if ( !visual_machine.get_register( "ZF" ) && !visual_machine.get_register( "ZF" ) )
    {
        do_jmp( dist, source );
    }
}

void do_jb( token dist, token source )
{
    if ( visual_machine.get_register( "SF" ) )
    {
        do_jmp( dist, source );
    }
}

void do_jnb( token dist, token source )
{
    if ( !visual_machine.get_register( "SF" ) )
    {
        do_jmp( dist, source );
    }
}

void do_call( token dist, token source )
{
    visual_machine.push( visual_machine.get_register( "PC" ) );
    if ( dist.type == MEMORY )
    {
        visual_machine.set_register( "PC", visual_machine.get_memory( dist.value ) );
    }
    else if ( dist.type == LABEL || dist.type == NUMBER || dist.type == VAR || dist.type == REGISTER )
    {
        visual_machine.set_register( "PC", dist.value );
    }
    else
    {
        DEBUG_INFO( "The destination should be a number or a variable!" );
    }
}

void do_ret( token dist, token source )
{

    visual_machine.set_register( "PC", visual_machine.top() );
    visual_machine.pop();
}

void load_file( std::string file_name )
{
    std::ifstream file( file_name );
    if ( !file.is_open() )
    {
        DEBUG_INFO( "File not found!" );
        return;
    }
    std::string line;
    while ( std::getline( file, line ) )
    {
        size_t index = 0;
        while ( line[index] == ' ' )
        {
            index++;
        }
        line.erase( 0, index );
        code_list.push_back( line );
    }
    file.close();
}
