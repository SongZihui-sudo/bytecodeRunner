#ifndef machine_hpp
#define machine_hpp

#include <iostream>
#include <string>

#define DEBUG_INFO( mesage )                                                               \
    std::cout << "File: " << __FILE__ << " line: " << __LINE__                             \
              << " Function: " << __FUNCTION__ << " Message: " << mesage << std::endl;

#define MEMORY_SIZE 2048
#define STACK_SIZE 128

/*
    ADDRESS SPACE
    0 ~ 511 memory
    512 ~ 639 stack
    640 ~ 2047 memory
*/

/**
 * @brief machine object
 *
 */
class machine
{
public:
    machine()  = default;
    ~machine() = default;

    /**
     * @brief the register which you want to print
     *
     * @param reg
     */
    void print_reg( std::string reg )
    {
#define xx( reg_, uppercase_reg )                                                          \
    if ( reg == #reg_ || reg == #uppercase_reg )                                           \
    {                                                                                      \
        std::cout << reg << ": " << std::hex << get_##uppercase_reg() << std::endl;        \
    }
        xx( eax, EAX ) else xx( ebx, EBX ) else xx( ecx, ECX ) else xx( edx, EDX ) else xx( esp, ESP ) else xx( ebp, EBP ) else xx( esi, ESI ) else xx( edi, EDI ) else xx(
        acc,
        ACC ) else xx( mq,
                       MQ ) else xx( r8,
                                     R8 ) else xx( r9,
                                                   R9 ) else xx( r10,
                                                                 R10 ) else xx( r11,
                                                                                R11 ) else xx( r12,
                                                                                               R12 ) else xx( r13,
                                                                                                              R13 ) else xx( r14, R14 ) else xx( r15, R15 )
#undef xx
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
     * @brief set EAX register
     *
     * @param value
     */
    void set_EAX( const unsigned int value ) { EAX = value; }

    /**
     * @brief set EBX register
     *
     * @param value
     */
    void set_EBX( const unsigned int value ) { EBX = value; }

    /**
     * @brief set ECX register
     *
     * @param value
     */
    void set_ECX( const unsigned int value ) { ECX = value; }

    /**
     * @brief set EDX register
     *
     * @param value
     */
    void set_EDX( const unsigned int value ) { EDX = value; }

    /**
     * @brief set ESP register
     *
     * @param value
     */
    void set_ESP( const unsigned int value ) { ESP = value; }

    /**
     * @brief set EBP register
     *
     * @param value
     */
    void set_EBP( const unsigned int value ) { EBP = value; }

    /**
     * @brief set ESI register
     *
     * @param value
     */
    void set_ESI( const unsigned int value ) { ESI = value; }

    /**
     * @brief set EDI register
     *
     * @param value
     */
    void set_EDI( const unsigned int value ) { EDI = value; }

    /**
     * @brief set ACC register
     *
     * @param value
     */
    void set_ACC( const unsigned int value ) { ACC = value; }

    /**
     * @brief set MQ register
     *
     * @param value
     */
    void set_MQ( const unsigned int value ) { MQ = value; }

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
     * @brief set R8 register
     *
     * @param value
     */
    void set_R8( const unsigned int value ) { R8 = value; }

    /**
     * @brief set R9 register
     *
     * @param value
     */
    void set_R9( const unsigned int value ) { R9 = value; }

    /**
     * @brief set R10 register
     *
     * @param value
     */
    void set_R10( const unsigned int value ) { R10 = value; }

    /**
     * @brief set R11 register
     *
     * @param value
     */
    void set_R11( const unsigned int value ) { R11 = value; }

    /**
     * @brief set R12 register
     *
     * @param value
     */
    void set_R12( const unsigned int value ) { R12 = value; }

    /**
     * @brief set R13 register
     *
     * @param value
     */
    void set_R13( const unsigned int value ) { R13 = value; }

    /**
     * @brief set R14 register
     *
     * @param value
     */
    void set_R14( const unsigned int value ) { R14 = value; }

    /**
     * @brief set R15 register
     *
     * @param value
     */
    void set_R15( const unsigned int value ) { R15 = value; }

    /**
     * @brief set PC register
     *
     * @param value
     */
    void set_PC( const unsigned int value ) { PC = value; }

    /**
     * @brief set ZF register
     *
     * @param value
     */
    void set_ZF( const unsigned int value ) { ZF = value; }

    /**
     * @brief set SF register
     *
     * @param value
     */
    void set_SF( const unsigned int value ) { SF = value; }

    /**
     * @brief get EAX register
     *
     * @return EAX value
     */
    unsigned int get_EAX() const { return EAX; }

    /**
     * @brief get EBX register
     *
     * @return EBX value
     */
    unsigned int get_EBX() const { return EBX; }

    /**
     * @brief get ECX register
     *
     * @return ECX value
     */
    unsigned int get_ECX() const { return ECX; }

    /**
     * @brief get EDX register
     *
     * @return EDX value
     */
    unsigned int get_EDX() const { return EDX; }

    /**
     * @brief get ESP register
     *
     * @return ESP value
     */
    unsigned int get_ESP() const { return ESP; }

    /**
     * @brief get EBP register
     *
     * @return EBP value
     */
    unsigned int get_EBP() const { return EBP; }

    /**
     * @brief get ESI register
     *
     * @return ESI value
     */
    unsigned int get_ESI() const { return ESI; }

    /**
     * @brief get EDI register
     *
     * @return EDI value
     */
    unsigned int get_EDI() const { return EDI; }

    /**
     * @brief set ACC register
     *
     * @return unsigned int
     */
    unsigned int get_ACC() const { return ACC; }

    /**
     * @brief get MQ register
     *
     * @return unsigned int
     */
    unsigned int get_MQ() const { return MQ; }

    /**
     * @brief get memory value
     *
     * @param index
     * @return memory value
     */
    unsigned int get_memory( const size_t index )
    {
        if ( index > MEMORY_SIZE )
        {
            return 0;
        }
        return memory[index];
    }

    /**
     * @brief set R8 register
     *
     * @param value
     */
    unsigned int get_R8() { return R8; }

    /**
     * @brief set R9 register
     *
     * @param value
     */
    unsigned int get_R9() { return R9; }

    /**
     * @brief set R10 register
     *
     * @param value
     */
    unsigned int get_R10() { return R10; }

    /**
     * @brief set R11 register
     *
     * @param value
     */
    unsigned int get_R11() { return R11; }

    /**
     * @brief set R12 register
     *
     * @param value
     */
    unsigned int get_R12() { return R12; }

    /**
     * @brief set R13 register
     *
     * @param value
     */
    unsigned int get_R13() { return R13; }

    /**
     * @brief set R14 register
     *
     * @param value
     */
    unsigned int get_R14() { return R14; }

    /**
     * @brief set R15 register
     *
     * @param value
     */
    unsigned int get_R15() { return R15; }

    /**
     * @brief get PC register
     *
     * @return unsigned int
     */
    unsigned int get_PC() { return PC; }

    /**
     * @brief get ZF register
     *
     * @return unsigned int
     */
    unsigned int get_ZF() { return ZF; }

    /**
     * @brief get SF register
     *
     * @return unsigned int
     */
    unsigned int get_SF() { return SF; }

public:
    void push( unsigned int value )
    {
        if ( ESP < 512 )
        {
            DEBUG_INFO( "The stack is full!" );
            return;
        }
        else
        {
            memory[ESP] = value;
            ESP--;
        }
    }

    void pop()
    {
        if ( ESP > 639 )
        {
            DEBUG_INFO( "The stack is empty!" );
            return;
        }
        ESP--;
    }

    unsigned int top() { return memory[ESP]; }

    bool stack_empty() { return ESP == 512; }

private:
    unsigned int ZF;
    unsigned int SF;
    unsigned int PC;
    unsigned int R8;
    unsigned int R9;
    unsigned int R10;
    unsigned int R11;
    unsigned int R12;
    unsigned int R13;
    unsigned int R14;
    unsigned int R15;
    unsigned int memory[MEMORY_SIZE];
    unsigned int EAX;
    unsigned int EBX;
    unsigned int ECX;
    unsigned int EDX;
    unsigned int ESP = 639;
    unsigned int EBP = 639;
    unsigned int ESI;
    unsigned int EDI;
    unsigned int ACC;
    unsigned int MQ;
};

// visual machine
extern machine visual_machine;
#endif
