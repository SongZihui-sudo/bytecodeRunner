#ifndef instruction_hpp
#define instruction_hpp

#include <string>
#include <unordered_map>
#include <functional>
#include <iostream>

#include "token.hpp"

#define DEBUG_INFO( mesage )                                                               \
    std::cout << "File: " << __FILE__ << " line: " << __LINE__                             \
              << " Function: " << __FUNCTION__ << " Message: " << mesage << std::endl;

/**
 * @brief the string is unsigned int number?
 *
 * @param str
 * @return true
 * @return false
 */
bool is_uint( const std::string str );

/**
 * @brief the string is int number?
 *
 * @param str
 * @return true
 * @return false
 */
bool is_int( const std::string str );

/**
 * @brief the string is float number?
 *
 * @param str
 * @return true
 * @return false
 */
bool is_float( const std::string str );

class instruction_runner
{
public:
    instruction_runner()  = default;
    ~instruction_runner() = default;

public:
    /**
     * @brief run the code
     *
     * @param line code line
     * @return true successfully
     * @return false failed
     */
    static bool do_instruction( std::vector< token > line );

    /*
     * @brief load file
     *
     * @param file_name
     */
    static void load_file( std::string file_name );

    /**
     * @brief do mov instruction
     *
     * @param code
     */
    static void do_mov( token dist, const token source );

    /**
     * @brief do add instruction
     *
     * @param code
     */
    static void do_add( token dist, const token source );

    /**
     * @brief do sub instruction
     *
     * @param code
     */
    static void do_sub( token dist, const token source );

    /**
     * @brief do div instruction
     *
     * @param code
     */
    static void do_div( token dist, const token source );

    /**
     * @brief do mul instruction
     *
     * @param code
     */
    static void do_mul( token dist, const token source );

    /**
     * @brief do push instruction
     *
     * @param code
     */
    static void do_push( token dist, const token source );

    /**
     * @brief do pop instruction
     *
     * @param code
     */
    static void do_pop( token dist, const token source );

    /**
     * @brief do jmp instruction
     *
     * @param code
     */
    static void do_jmp( token dist, const token source );

    /**
     * @brief do cmp instruction
     *
     * @param code
     */
    static void do_cmp( token dist, const token source );

    /**
     * @brief do je instruction
     *
     * @param code
     */
    static void do_je( token dist, const token source );

    /**
     * @brief do jne instruction
     *
     * @param code
     */
    static void do_jne( token dist, const token source );

    /**
     * @brief do call instruction
     *
     * @param code
     */
    static void do_call( token dist, const token source );

    /**
     * @brief do ret instruction
     *
     * @param code
     */
    static void do_ret( token dist, const token source );

    /**
     * @brief do jbe instruction
     *
     * @param code
     */
    static void do_jbe( token dist, const token source );

    /**
     * @brief do ja instruction
     *
     * @param code
     */
    static void do_ja( token dist, const token source );

    /**
     * @brief do jb instruction
     *
     * @param code
     */
    static void do_jb( token dist, const token source );

    /**
     * @brief do jnb instruction
     *
     * @param code
     */
    static void do_jnb( token dist, const token source );

    /**
     * @brief do let instruction
     *
     * @param code
     */
    static void do_let( token dist, const token source );

    /**
     * @brief do expression
     *
     * @param source
     */
    static token do_expression( const token source );

    static std::unordered_map< std::string, std::function< void( token, token ) > > do_instruction_funcs;
};

#endif
