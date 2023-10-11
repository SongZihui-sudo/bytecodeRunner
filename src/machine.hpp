#ifndef machine_hpp
#define machine_hpp

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <functional>

#define DEBUG_INFO( mesage )                                                               \
    std::cout << "File: " << __FILE__ << " line: " << __LINE__                             \
              << " Function: " << __FUNCTION__ << " Message: " << mesage << std::endl;

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
            std::cout << reg << ": " << std::hex << register_map[reg] << std::endl;
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
                    std::cout << "memory[" << i << "]: " << memory[i] << std::endl;
                }
            }
            else
            {
                for ( size_t i = start; i > start + size; i-- )
                {
                    std::cout << "memory[" << i << "]: " << memory[i] << std::endl;
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
            std::cout << "stack[" << i << "]: " << memory[i] << std::endl;
        }
    }

public:
    /**
     * @brief Set the memory object
     *
     * @param index
     * @param value
     */
    void set_memory( const size_t index, const unsigned int value )
    {
        if ( index > MEMORY_SIZE )
        {
            return;
        }
        if ( index <= 638 && index >= 512 )
        {
            DEBUG_INFO( "The address is belong to stack can not be set!" )
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
    unsigned int get_memory( const size_t index )
    {
        if ( index > MEMORY_SIZE || index < 0 )
        {
            return 0;
        }
        return memory[index];
    }

    /**
     * @brief set register value
     *
     * @param value
     */
    unsigned int get_register( std::string reg )
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
    void set_register( std::string reg, unsigned int value )
    {
        std::transform( reg.begin(), reg.end(), reg.begin(), ::toupper );
        register_map.erase( reg );
        register_map[reg] = value;
    }

public:
    void push( unsigned int value )
    {
        if ( register_map["ESP"] > 511 )
        {
            DEBUG_INFO( "The stack is full!" );
            return;
        }
        else
        {
            memory[register_map["ESP"]] = value;
            register_map["ESP"]++;
        }
    }

    void pop()
    {
        if ( !register_map["ESP"] )
        {
            DEBUG_INFO( "The stack is empty!" );
            return;
        }
        register_map["ESP"]--;
    }

    unsigned int top()
    {
        if ( !register_map["ESP"] )
        {
            DEBUG_INFO( "The stack is empty!" );
            return 0;
        }
        return memory[register_map["ESP"] - 1];
    }

    bool stack_empty() { return register_map["ESP"] == 511; }

private:
    std::unordered_map< std::string, unsigned int > register_map
    = { { "ZF", 0 },  { "SF", 0 },  { "PC", 0 },  { "R8", 0 },  { "R9", 0 },  { "R10", 0 },
        { "R11", 0 }, { "R12", 0 }, { "R13", 0 }, { "R14", 0 }, { "R15", 0 }, { "EAX", 0 },
        { "EBX", 0 }, { "ECX", 0 }, { "EDX", 0 }, { "ESP", 0 }, { "EBP", 0 }, { "ESI", 0 },
        { "EDI", 0 }, { "ACC", 0 }, { "MQ", 0 } };
    unsigned int memory[MEMORY_SIZE];

public:
};

#endif
