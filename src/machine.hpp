#ifndef machine_hpp
#define machine_hpp

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <functional>

#include "token.hpp"

#define DEBUG_INFO( mesage )                                                               \
    []()                                                                                   \
    {                                                                                      \
        std::cout << "File: " << __FILE__ << " line: " << __LINE__                         \
                  << " Function: " << __FUNCTION__ << " Message: " << mesage << std::endl; \
    }

#define MEMORY_SIZE 2048
#define STACK_SIZE 128

/*
    ADDRESS SPACE
    0 ~ 511 stack
    512 ~ 2047 memory
*/

/**
 * @brief machine object
 *
 */
class machine_state
{
public:
    machine_state()  = default;
    ~machine_state() = default;

    /**
     * @brief the register which you want to print
     *
     * @param reg
     */
    void print_reg( std::string reg )
    {
        std::transform( reg.begin(), reg.end(), reg.begin(), ::toupper );
        if ( register_map.count( reg ) )
        {
            std::cout << reg << ": " << std::hex << GET_UINT_VALUE( register_map[reg] ) << std::endl;
        }
        else
        {
            DEBUG_INFO( "UNKONEN REGISTER NAME!" );
        }
    }

    /**
     * @brief print memory
     *
     * @param start start memory index
     * @param size memory size
     */
    void print_memory( size_t start, size_t size )
    {
        if ( start <= MEMORY_SIZE && start + size <= MEMORY_SIZE && start >= 0 && start + size >= 0 )
        {
            if ( size > 0 )
            {
                for ( size_t i = start; i < start + size; i++ )
                {
                    std::cout << "memory[" << i << "]: " << GET_UINT_VALUE( memory[i] ) << std::endl;
                }
            }
            else
            {
                for ( size_t i = start; i > start + size; i-- )
                {
                    std::cout << "memory[" << i << "]: " << GET_UINT_VALUE( memory[i] ) << std::endl;
                }
            }
        }
        else
        {
            DEBUG_INFO( "The index is out of the range!" );
        }
    }

    /**
     * @brief print stack
     *
     */
    void print_stack()
    {
        for ( size_t i = 639; i >= 512; i-- )
        {
            std::cout << "stack[" << i << "]: " << GET_UINT_VALUE( memory[i] ) << std::endl;
        }
    }

public:
    /**
     * @brief Set the memory object
     *
     * @param index
     * @param value
     */
    void set_memory( const size_t index, const token_value value )
    {
        if ( index > MEMORY_SIZE )
        {
            DEBUG_INFO( "The index is out of the range!" );
            return;
        }
        if ( index <= 638 && index >= 512 )
        {
            DEBUG_INFO( "The address is belong to stack can not be set!" );
            return;
        }
        memory[index] = value;
    }

    /**
     * @brief get memory value
     *
     * @param index
     * @return memory value
     */
    token_value get_memory( const size_t index )
    {
        if ( index > MEMORY_SIZE || index < 0 )
        {
            ;
        }
        return memory[index];
    }

    /**
     * @brief set register value
     *
     * @param value
     */
    token_value get_register( std::string reg )
    {
        std::transform( reg.begin(), reg.end(), reg.begin(), ::toupper );
        return register_map[reg];
    }

    /**
     * @brief is a register
     *
     * @param value
     */
    bool is_register( std::string reg )
    {
        std::transform( reg.begin(), reg.end(), reg.begin(), ::toupper );
        return register_map.count( reg );
    }

    /**
     * @brief set register value
     *
     * @param value
     */
    void set_register( std::string reg, const token_value value )
    {
        std::transform( reg.begin(), reg.end(), reg.begin(), ::toupper );
        register_map.erase( reg );
        register_map[reg] = value;
    }

public:
    void push( token_value value )
    {
        if ( register_map["ESP"] > INT_VALUE( 511 ) )
        {
            DEBUG_INFO( "The stack is full!" );
        }
        else
        {
            memory[GET_UINT_VALUE( register_map["ESP"] )] = value;
            register_map["ESP"] = register_map["ESP"] + INT_VALUE( 1 );
        }
    }

    void pop()
    {
        if ( register_map["ESP"] == INT_VALUE( 0 ) )
        {
            DEBUG_INFO( "The stack is empty!" );
            return;
        }
        register_map["ESP"] = register_map["ESP"] - INT_VALUE( 1 );
    }

    token_value top()
    {
        if ( register_map["ESP"] == INT_VALUE( 0 ) )
        {
            DEBUG_INFO( "The stack is empty!" );
            return {};
        }
        return memory[GET_UINT_VALUE( ( register_map["ESP"] - INT_VALUE( 1 ) ) )];
    }

    bool stack_empty() { return register_map["ESP"] == INT_VALUE( 511 ); }

private:
    std::unordered_map< std::string, token_value > register_map
    = { { "ZF", BOOL_VALUE( false ) }, { "SF", BOOL_VALUE( false ) },
        { "PC", UINT_VALUE( 0 ) },     { "R8", UINT_VALUE( 0 ) },
        { "R9", UINT_VALUE( 0 ) },     { "R10", UINT_VALUE( 0 ) },
        { "R11", UINT_VALUE( 0 ) },    { "R12", UINT_VALUE( 0 ) },
        { "R13", UINT_VALUE( 0 ) },    { "R14", UINT_VALUE( 0 ) },
        { "R15", UINT_VALUE( 0 ) },    { "EAX", UINT_VALUE( 0 ) },
        { "EBX", UINT_VALUE( 0 ) },    { "ECX", UINT_VALUE( 0 ) },
        { "EDX", UINT_VALUE( 0 ) },    { "ESP", UINT_VALUE( 0 ) },
        { "EBP", UINT_VALUE( 0 ) },    { "ESI", UINT_VALUE( 0 ) },
        { "EDI", UINT_VALUE( 0 ) },    { "ACC", UINT_VALUE( 0 ) },
        { "MQ", UINT_VALUE( 0 ) } };
    token_value memory[MEMORY_SIZE];

public:
};

#endif
