#ifndef instruction_hpp
#define instruction_hpp

#include <string>
#include <unordered_map>
#include <functional>

#define DEBUG_INFO( mesage )                                                               \
    std::cout << "File: " << __FILE__ << " line: " << __LINE__                             \
              << " Function: " << __FUNCTION__ << " Message: " << mesage << std::endl;

extern std::unordered_map< std::string, size_t > label_table;

#define el else

#define register_xx                                                                        \
    xx( eax, EAX ) el xx( ebx, EBX )                                                       \
    el xx( ecx, ECX )                                                                      \
    el xx( edx, EDX )                                                                      \
    el xx( esp, ESP )                                                                      \
    el xx( ebp, EBP )                                                                      \
    el xx( esi, ESI )                                                                      \
    el xx( edi, EDI )                                                                      \
    el xx( acc, ACC )                                                                      \
    el xx( mq, MQ )                                                                        \
    el xx( r8, R8 )                                                                        \
    el xx( r9, R9 )                                                                        \
    el xx( r10, R10 )                                                                      \
    el xx( r11, R11 )                                                                      \
    el xx( r12, R12 )                                                                      \
    el xx( r13, R13 )                                                                      \
    el xx( r14, R14 )                                                                      \
    el xx( r15, R15 )

#define instruction_xx                                                                     \
    xx( mov, MOV ) el xx( add, ADD )                                                       \
    el xx( sub, SUB )                                                                      \
    el xx( mul, MUL )                                                                      \
    el xx( div, DIV )                                                                      \
    el xx( push, PUSH )                                                                    \
    el xx( pop, POP )                                                                      \
    el xx( jmp, JMP )                                                                      \
    el xx( cmp, CMP )                                                                      \
    el xx( je, JE )                                                                        \
    el xx( jne, JNE )                                                                      \
    el xx( jbe, JBE )                                                                      \
    el xx( ja, JA )                                                                        \
    el xx( jb, JB )                                                                        \
    el xx( jnb, JNB )                                                                      \
    el xx( call, CALL )                                                                    \
    el xx( ret, RET )

#define get_word()                                                                         \
    size_t space    = code.find( ' ' );                                                    \
    std::string tmp = code.substr( index, space );                                         \
    code            = code.substr( space + 1, code.size() );

#define take_number( line )                                                                \
    if ( isNumber( tmp ) )                                                                 \
    {                                                                                      \
        line;                                                                              \
        pos[i] = std::stoul( tmp );                                                        \
    }

#define take_memory( line )                                                                  \
    if ( tmp[0] == '[' )                                                                     \
    {                                                                                        \
        if ( tmp.back() != ']' )                                                             \
        {                                                                                    \
            DEBUG_INFO( "The parentheses cannot match!" );                                   \
            return;                                                                          \
        }                                                                                    \
        pos[i] = visual_machine.get_memory( std::stoul( tmp.substr( 1, tmp.size() - 2 ) ) ); \
        line;                                                                                \
    }

#define take_label(key) if (label_table.count(key)) { pos[i] = label_table[key]; }

/**
 * @brief the string is number?
 *
 * @param str
 * @return true
 * @return false
 */
bool isNumber( const std::string& str );

/**
 * @brief run the code
 *
 * @param line code line
 * @return true successfully
 * @return false failed
 */
bool do_instruction( std::string line );

/**
 * @brief do mov instruction
 *
 * @param code
 */
void do_mov( std::string code );

/**
 * @brief do add instruction
 *
 * @param code
 */
void do_add( std::string code );

/**
 * @brief do sub instruction
 *
 * @param code
 */
void do_sub( std::string code );

/**
 * @brief do div instruction
 *
 * @param code
 */
void do_div( std::string code );

/**
 * @brief do mul instruction
 *
 * @param code
 */
void do_mul( std::string code );

/**
 * @brief do push instruction
 *
 * @param code
 */
void do_push( std::string code );

/**
 * @brief do pop instruction
 *
 * @param code
 */
void do_pop( std::string code );

/**
 * @brief do jmp instruction
 *
 * @param code
 */
void do_jmp( std::string code );

/**
 * @brief do cmp instruction
 *
 * @param code
 */
void do_cmp( std::string code );

/**
 * @brief do je instruction
 *
 * @param code
 */
void do_je( std::string code );

/**
 * @brief do jne instruction
 *
 * @param code
 */
void do_jne( std::string code );

/**
 * @brief do call instruction
 *
 * @param code
 */
void do_call( std::string code );

/**
 * @brief do ret instruction
 *
 * @param code
 */
void do_ret( std::string code );

/**
 * @brief do jbe instruction
 *
 * @param code
 */
void do_jbe( std::string code );

/**
 * @brief do ja instruction
 *
 * @param code
 */
void do_ja( std::string code );

/**
 * @brief do jb instruction
 *
 * @param code
 */
void do_jb( std::string code );

/**
 * @brief do jnb instruction
 *
 * @param code
 */
void do_jnb( std::string code );

/**
 * @brief do jae instruction
 *
 * @param code
 */
void do_code( std::function< void( unsigned int*, unsigned int* ) > func1, std::string code, int count );

#endif
