#include "instruction.hpp"
#include "machine.hpp"

std::unordered_map< std::string, size_t > label_table;

bool isNumber( const std::string& str )
{
    for ( char const& c : str )
    {
        if ( std::isdigit( c ) == 0 )
            return false;
    }
    return true;
}

bool do_instruction( std::string line )
{
    size_t index    = 0;
    std::string tmp = line.substr( index, line.find( ' ' ) );
#define xx( instruction_name, instuction_name_up )                                         \
    if ( tmp == #instruction_name || tmp == #instuction_name_up )                          \
    {                                                                                      \
        line.erase( 0, std::string( #instruction_name ).size() + 1 );                      \
        do_##instruction_name( line );                                                     \
    }
    instruction_xx
#undef xx
    else
    {
        DEBUG_INFO( "Error Code!" )
        return false;
    }
    return true;
}

void do_mov( std::string code )
{
    const size_t index  = 0;
    unsigned int pos[2] = { 0, 0 };
    for ( size_t i = 0; i < 2; i++ )
    {
        get_word();
        take_number( if ( i == 1 ) {
            DEBUG_INFO( "The destination cannot be a number!" );
            return;
        } ) else take_memory( if ( i == 1 ) { visual_machine.set_memory( pos[1], pos[0] ); } )
#define xx( reg, uppercase_reg )                                                           \
    if ( tmp == #reg || tmp == #uppercase_reg )                                            \
    {                                                                                      \
        pos[i] = visual_machine.get_##uppercase_reg();                                     \
        if ( i == 1 )                                                                      \
        {                                                                                  \
            visual_machine.set_##uppercase_reg( pos[0] );                                  \
        }                                                                                  \
    }
        register_xx
#undef xx
        else
        {
            DEBUG_INFO( "The register name is wrong! Register Name: " + tmp );
            return;
        }
    }
}

void do_add( std::string code )
{
    do_code( []( unsigned int* pos1, unsigned int* pos2 )
             { visual_machine.set_ACC( ( *pos1 ) + ( *pos2 ) ); },
             code,
             2 );
}

void do_sub( std::string code )
{
    do_code( []( unsigned int* pos1, unsigned int* pos2 )
             { visual_machine.set_ACC( *( pos2 ) - *( pos1 ) ); },
             code,
             2 );
}

void do_div( std::string code )
{
    do_code( []( unsigned int* pos1, unsigned int* pos2 )
             { visual_machine.set_MQ( ( *pos2 ) / ( *pos1 ) ); },
             code,
             2 );
}

void do_mul( std::string code )
{
    do_code( []( unsigned int* pos1, unsigned int* pos2 )
             { visual_machine.set_MQ( ( *pos1 ) * ( *pos2 ) ); },
             code,
             2 );
}

void do_push( std::string code )
{
    do_code( []( unsigned int* pos1, unsigned int* pos2 ) { visual_machine.push( *pos1 ); }, code, 1 );
}

void do_pop( std::string code )
{
    if ( isNumber( code ) && !code.empty() )
    {
        DEBUG_INFO( "The destination should not be a number!" );
    }
    else
    {
#define xx( reg, uppercase_reg )                                                           \
    if ( code == #reg || code == #uppercase_reg )                                          \
    {                                                                                      \
        unsigned int tmp = visual_machine.top();                                           \
        visual_machine.set_##uppercase_reg( tmp );                                         \
    }
        register_xx
#undef xx
    }
    visual_machine.pop();
}

void do_jmp( std::string code )
{
    do_code( []( unsigned int* pos1, unsigned int* pos2 ) { visual_machine.set_PC( *pos1 ); }, code, 1 );
}

void do_cmp( std::string code )
{
    do_code(
    []( unsigned int* pos1, unsigned int* pos2 )
    {
        if ( *pos1 == *pos2 )
        {
            visual_machine.set_ZF( 1 );
        }
        else
        {
            visual_machine.set_ZF( 0 );
        }
        if ( *pos1 > *pos2 )
        {
            visual_machine.set_SF( 1 );
        }
        else
        {
            visual_machine.set_SF( 0 );
        }
    },
    code,
    2 );
}

void do_je( std::string code )
{
    if ( visual_machine.get_ZF() )
    {
        do_jmp( code );
    }
}

void do_jne( std::string code )
{
    if ( !visual_machine.get_ZF() )
    {
        do_jmp( code );
    }
}

void do_jbe( std::string code )
{
    if ( visual_machine.get_ZF() || visual_machine.get_SF() )
    {
        do_jmp( code );
    }
}

void do_ja( std::string code )
{
    if ( !visual_machine.get_ZF() && !visual_machine.get_SF() )
    {
        do_jmp( code );
    }
}

void do_jb( std::string code )
{
    if ( visual_machine.get_SF() )
    {
        do_jmp( code );
    }
}

void do_jnb( std::string code )
{
    if ( !visual_machine.get_SF() )
    {
        do_jmp( code );
    }
}

void do_call( std::string code )
{
    do_code(
    []( unsigned int* pos1, unsigned int* pos2 )
    {
        visual_machine.push( visual_machine.get_PC() );
        visual_machine.set_PC( *pos1 );
    },
    code,
    1 );
}

void do_ret( std::string code )
{
    visual_machine.set_PC( visual_machine.top() );
    visual_machine.pop();
    unsigned int tmp = visual_machine.top();
    visual_machine.set_EBP( visual_machine.top() );
    visual_machine.pop();
    visual_machine.set_ESP( tmp );
}

void do_code( std::function< void( unsigned int*, unsigned int* ) > func, std::string code, int count )
{
    const size_t index  = 0;
    unsigned int pos[2] = { 0, 0 };
    size_t space        = code.find( ' ' );
    for ( size_t i = 0; i < count; i++ )
    {
        std::string tmp = code.substr( index, space );
        code            = code.substr( space + 1, code.size() );
        take_number() else take_memory() else take_label( code )
#define xx( reg, uppercase_reg )                                                           \
    if ( tmp == #reg || tmp == #uppercase_reg )                                            \
    {                                                                                      \
        pos[i] = visual_machine.get_##uppercase_reg();                                     \
    }
        register_xx
#undef xx
        space
        = code.find( ' ' );
    }
    func( &pos[0], &pos[1] );
}
