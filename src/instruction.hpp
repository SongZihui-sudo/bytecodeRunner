#ifndef instruction_hpp
#define instruction_hpp

#include <string>
#include <unordered_map>
#include <functional>
#include <iostream>

#define DEBUG_INFO( mesage )                                                               \
    std::cout << "File: " << __FILE__ << " line: " << __LINE__                             \
              << " Function: " << __FUNCTION__ << " Message: " << mesage << std::endl;

extern std::unordered_map< std::string, unsigned int > var_table;

extern std::vector< std::string > code_list;

extern std::unordered_map< std::string, size_t > label_table;

#define el else

enum token_type
{
    NUMBER,
    REGISTER,
    MEMORY,
    LABEL,
    VAR,
    OPER,
    UNKNOWN
};

struct token
{
    std::string name;
    unsigned int value;
    token_type type;
};

extern const std::unordered_map< std::string, std::function< void( token, token ) > > do_instruction_func;

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
bool do_instruction( std::vector< token > line );

/**
 * @brief do mov instruction
 *
 * @param code
 */
void do_mov( token dist, token source );

/**
 * @brief do add instruction
 *
 * @param code
 */
void do_add( token dist, token source );

/**
 * @brief do sub instruction
 *
 * @param code
 */
void do_sub( token dist, token source );

/**
 * @brief do div instruction
 *
 * @param code
 */
void do_div( token dist, token source );

/**
 * @brief do mul instruction
 *
 * @param code
 */
void do_mul( token dist, token source );

/**
 * @brief do push instruction
 *
 * @param code
 */
void do_push( token dist, token source );

/**
 * @brief do pop instruction
 *
 * @param code
 */
void do_pop( token dist, token source );

/**
 * @brief do jmp instruction
 *
 * @param code
 */
void do_jmp( token dist, token source );

/**
 * @brief do cmp instruction
 *
 * @param code
 */
void do_cmp( token dist, token source );

/**
 * @brief do je instruction
 *
 * @param code
 */
void do_je( token dist, token source );

/**
 * @brief do jne instruction
 *
 * @param code
 */
void do_jne( token dist, token source );

/**
 * @brief do call instruction
 *
 * @param code
 */
void do_call( token dist, token source );

/**
 * @brief do ret instruction
 *
 * @param code
 */
void do_ret( token dist, token source );

/**
 * @brief do jbe instruction
 *
 * @param code
 */
void do_jbe( token dist, token source );

/**
 * @brief do ja instruction
 *
 * @param code
 */
void do_ja( token dist, token source );

/**
 * @brief do jb instruction
 *
 * @param code
 */
void do_jb( token dist, token source );

/**
 * @brief do jnb instruction
 *
 * @param code
 */
void do_jnb( token dist, token source );

/*
 * @brief load file
 *
 * @param file_name
 */
void load_file( std::string file_name );

#endif
