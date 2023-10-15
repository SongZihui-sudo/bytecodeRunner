#include <sstream>
#include <fstream>
#include <array>
#include <stack>

#include "instruction.hpp"
#include "state.hpp"
#include "token.hpp"

std::unordered_map< std::string, std::function< void( token, token ) > > instruction_runner::do_instruction_funcs
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
    { "PR",
      []( token arg1, token arg2 )
      { visual_machine.visual_machine_state.print_reg( arg1.name ); } },
    { "PM",
      []( token arg1, token arg2 )
      {
          std::cout << "Please input the start index: ";
          unsigned int start;
          std::cin >> start;
          std::cout << "Please input the read size: ";
          unsigned int read_size;
          std::cin >> read_size;
          visual_machine.visual_machine_state.print_memory( start, read_size );
      } },
    { "PS",
      []( token arg1, token arg2 ) { visual_machine.visual_machine_state.print_stack(); } },
    { "MOV", instruction_runner::do_mov },
    { "ADD", instruction_runner::do_add },
    { "SUB", instruction_runner::do_sub },
    { "MUL", instruction_runner::do_mul },
    { "DIV", instruction_runner::do_div },
    { "PUSH", instruction_runner::do_push },
    { "POP", instruction_runner::do_pop },
    { "JMP", instruction_runner::do_jmp },
    { "CMP", instruction_runner::do_cmp },
    { "JE", instruction_runner::do_je },
    { "JNE", instruction_runner::do_jne },
    { "JBE", instruction_runner::do_jbe },
    { "JA", instruction_runner::do_ja },
    { "JB", instruction_runner::do_jb },
    { "JNB", instruction_runner::do_jnb },
    { "CALL", instruction_runner::do_call },
    { "RET", instruction_runner::do_ret },
    { "LET", instruction_runner::do_let } };

#define value_get( val, key )                                                              \
    switch ( key.type )                                                                    \
    {                                                                                      \
        case MEMORY:                                                                       \
            val = visual_machine.visual_machine_state.get_memory( GET_UINT_VALUE( val ) ); \
            break;                                                                         \
        case REGISTER:                                                                     \
            val = visual_machine.visual_machine_state.get_register( key.name );            \
            break;                                                                         \
        case VAR:                                                                          \
            val = visual_machine.var_table[key.name];                                      \
            break;                                                                         \
        case NUMBER:                                                                       \
            val = key.value;                                                               \
            break;                                                                         \
        case EXPRESSION:                                                                   \
            val = visual_machine.visual_machine_state.get_memory(                          \
            GET_UINT_VALUE( do_expression( key ).value ) );                                \
            break;                                                                         \
        default:                                                                           \
            DEBUG_INFO( "The destination should be a register or a variable!" );           \
    }

bool is_uint( const std::string str )
{
    for ( char const& c : str )
    {
        if ( std::isdigit( c ) == 0 )
            return false;
    }
    return true;
}

bool is_int( const std::string str )
{
    std::string tmp = str;
    if ( tmp[0] == '+' || tmp[0] == '-' )
    {
        tmp.erase( 0, 1 );
    }
    if ( is_uint( tmp ) )
    {
        return true;
    }
    return false;
}

bool is_float( const std::string str )
{
    std::string tmp = str;
    if ( tmp[0] == '+' || tmp[0] == '-' )
    {
        tmp.erase( 0, 1 );
    }
    size_t has_dot = tmp.find( "." );
    if ( has_dot != -1 )
    {
        tmp.erase( has_dot, 1 );
    }
    if ( is_uint( tmp ) )
    {
        return true;
    }
    return false;
}

bool is_char( const std::string str )
{
    std::string tmp = str;
    if ( tmp[0] == '\'' && tmp[str.size() - 1] == '\'' )
    {
        tmp.pop_back();
        tmp.erase( 0, 1 );
        if ( tmp.size() == 1 )
        {
            return true;
        }
    }
    return false;
}

bool instruction_runner::do_instruction( std::vector< token > line )
{
    line.push_back( token() );
    line.push_back( token() );
    if ( do_instruction_funcs.count( line[0].name ) )
    {
        do_instruction_funcs.at( line[0].name )( line[1], line[2] );
        return true;
    }
    return true;
}

void instruction_runner::do_mov( token dist, const token source )
{
    if ( dist.type == NUMBER )
    {
        DEBUG_INFO( "The destination should not be a number!" );
    }
    else
    {
        token_value tmp;
        value_get( tmp, source );
        switch ( dist.type )
        {
            case REGISTER:
                visual_machine.visual_machine_state.set_register( dist.name, tmp );
                break;
            case VAR:
                visual_machine.var_table[dist.name] = tmp;
                break;
            case MEMORY:
                visual_machine.visual_machine_state.set_memory( GET_UINT_VALUE( dist.value ), tmp );
                break;
            case EXPRESSION:
                visual_machine.visual_machine_state.set_memory(
                GET_UINT_VALUE( visual_machine.visual_machine_state.get_register( dist.name ) ), tmp );
                break;
            default:
                DEBUG_INFO( "The destination should be a register or a variable!" );
        }
    }
}

void instruction_runner::do_add( token dist, const token source )
{
    token_value tmp1 = dist.value;
    token_value tmp2 = source.value;
    value_get( tmp1, dist );
    value_get( tmp2, source );
    visual_machine.visual_machine_state.set_register( "ACC", tmp1 + tmp2 );
}

void instruction_runner::do_sub( token dist, const token source )
{
    token_value tmp1 = dist.value;
    token_value tmp2 = source.value;
    value_get( tmp1, dist );
    value_get( tmp2, source );
    visual_machine.visual_machine_state.set_register( "ACC", tmp1 - tmp2 );
}

void instruction_runner::do_div( token dist, const token source )
{
    token_value tmp1 = dist.value;
    token_value tmp2 = source.value;
    value_get( tmp1, dist );
    value_get( tmp2, source );
    visual_machine.visual_machine_state.set_register( "MQ", tmp1 / tmp2 );
}

void instruction_runner::do_mul( token dist, const token source )
{
    token_value tmp1 = dist.value;
    token_value tmp2 = source.value;
    value_get( tmp1, dist );
    value_get( tmp2, source );
    visual_machine.visual_machine_state.set_register( "MQ", tmp1 * tmp2 );
}

void instruction_runner::do_push( token dist, const token source )
{
    switch ( dist.type )
    {
        case NUMBER:
            visual_machine.visual_machine_state.push( dist.value );
            break;
        case REGISTER:
            visual_machine.visual_machine_state.push(
            visual_machine.visual_machine_state.get_register( dist.name ) );
            break;
        case VAR:
            visual_machine.visual_machine_state.push( visual_machine.var_table[dist.name] );
            break;
        case MEMORY:
            visual_machine.visual_machine_state.push(
            visual_machine.visual_machine_state.get_memory( GET_UINT_VALUE( dist.value ) ) );
            break;
        default:
            DEBUG_INFO( "The dist should be a number or a register or a variable!" );
    }
}

void instruction_runner::do_pop( token dist, const token source )
{
    if ( dist.type == NUMBER )
    {
        DEBUG_INFO( "The destination should not be a number!" );
        return;
    }
    else
    {
        token_value tmp = visual_machine.visual_machine_state.top();
        switch ( dist.type )
        {
            case REGISTER:
                visual_machine.visual_machine_state.set_register( dist.name, tmp );
                break;
            case VAR:
                visual_machine.var_table[dist.name] = tmp;
                break;
            case MEMORY:
                visual_machine.visual_machine_state.set_memory( GET_UINT_VALUE( dist.value ), tmp );
                break;
            default:
                DEBUG_INFO( "The destination should be a register or a variable!" );
        }
    }
    visual_machine.visual_machine_state.pop();
}

void instruction_runner::do_jmp( token dist, const token source )
{
    token_value tmp;
    value_get( tmp, dist );
    tmp = tmp - UINT_VALUE( 1 );
    if ( tmp > UINT_VALUE( ( unsigned int )visual_machine.code_list.size() ) || tmp < INT_VALUE( 0 ) )
    {
        DEBUG_INFO( "The address is out of the range!" );
        return;
    }
    visual_machine.visual_machine_state.set_register( "PC", tmp );
}

void instruction_runner::do_cmp( token dist, const token source )
{
    token_value tmp1 = dist.value;
    token_value tmp2 = source.value;
    value_get( tmp1, dist );
    value_get( tmp2, source );
    visual_machine.visual_machine_state.set_register( "ZF", BOOL_VALUE( ( tmp1 == tmp2 ) ) );
    visual_machine.visual_machine_state.set_register( "SF", BOOL_VALUE( ( tmp1 < tmp2 ) ) );
}

void instruction_runner::do_je( token dist, const token source )
{
    if ( GET_BOOL_VALUE( visual_machine.visual_machine_state.get_register( "ZF" ) ) )
    {
        do_jmp( dist, source );
    }
}

void instruction_runner::do_jne( token dist, const token source )
{
    if ( !GET_BOOL_VALUE( visual_machine.visual_machine_state.get_register( "ZF" ) ) )
    {
        do_jmp( dist, source );
    }
}

void instruction_runner::do_jbe( token dist, const token source )
{
    if ( GET_BOOL_VALUE( visual_machine.visual_machine_state.get_register( "ZF" ) )
         || GET_BOOL_VALUE( visual_machine.visual_machine_state.get_register( "SF" ) ) )
    {
        do_jmp( dist, source );
    }
}

void instruction_runner::do_ja( token dist, const token source )
{
    if ( !GET_BOOL_VALUE( visual_machine.visual_machine_state.get_register( "ZF" ) )
         && !GET_BOOL_VALUE( visual_machine.visual_machine_state.get_register( "SF" ) ) )
    {
        do_jmp( dist, source );
    }
}

void instruction_runner::do_jb( token dist, const token source )
{
    if ( GET_UINT_VALUE( visual_machine.visual_machine_state.get_register( "SF" ) ) )
    {
        do_jmp( dist, source );
    }
}

void instruction_runner::do_jnb( token dist, const token source )
{
    if ( !GET_UINT_VALUE( visual_machine.visual_machine_state.get_register( "SF" ) ) )
    {
        do_jmp( dist, source );
    }
}

void instruction_runner::do_call( token dist, const token source )
{
    visual_machine.visual_machine_state.push(
    visual_machine.visual_machine_state.get_register( "PC" ) );
    if ( dist.type == MEMORY )
    {
        visual_machine.visual_machine_state.set_register(
        "PC", visual_machine.visual_machine_state.get_memory( GET_UINT_VALUE( dist.value ) ) );
    }
    else if ( dist.type == LABEL || dist.type == NUMBER || dist.type == VAR || dist.type == REGISTER )
    {
        visual_machine.visual_machine_state.set_register( "PC", dist.value );
    }
    else
    {
        DEBUG_INFO( "The destination should be a number or a variable!" );
    }
}

void instruction_runner::do_ret( token dist, const token source )
{
    visual_machine.visual_machine_state.set_register( "PC",
                                                      visual_machine.visual_machine_state.top() );
    visual_machine.visual_machine_state.pop();
}

void instruction_runner::load_file( std::string file_name )
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
        visual_machine.code_list.push_back( line );
    }
    file.close();
}

void instruction_runner::do_let( token dist, const token source )
{
    token_value tmp1;
    value_get( tmp1, source );
    visual_machine.var_table[dist.name] = tmp1;
}

token instruction_runner::do_expression( const token source )
{
    token expression;
    std::stack< char > operators;
    std::stack< token_value > numbers;
    std::string buffer;
    token_value temp;
    std::string suffix;
    for ( char cc : source.name )
    {
        switch ( cc )
        {
            case '(':
                operators.push( cc );
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                /* is a register */
                if ( visual_machine.visual_machine_state.is_register( buffer ) )
                {
                    temp = visual_machine.visual_machine_state.get_register( buffer );
                }
                /* is a var */
                else if ( visual_machine.var_table.count( buffer ) )
                {
                    temp = visual_machine.var_table[buffer];
                }
                /* is number */
                else
                {
                    /* uint number */
                    if ( is_uint( buffer ) )
                    {
                        temp = UINT_VALUE( std::stoul( buffer ) );
                    }
                    /* int number */
                    else if ( is_int( buffer ) )
                    {
                        temp = INT_VALUE( std::stoi( buffer ) );
                    }
                    /* float number */
                    else if ( is_float( buffer ) )
                    {
                        temp = FLOAT_VALUE( std::stod( buffer ) );
                    }
                    else
                    {
                        DEBUG_INFO( "UNKNOEN EXPRESSION " << buffer );
                    }
                }
                numbers.push( temp );
                buffer.clear();
                /* compare operator */
                if ( operators.empty()
                     || ( ( cc == '*' || cc == '/' )
                          && ( operators.top() == '+' || operator.top() == '-' ) ) )
                {
                    operators.push( cc );
                }
                else
                {
                }
                break;
            default:
                buffer.push_back( cc );
                break;
        }
    }
    return expression;
}
