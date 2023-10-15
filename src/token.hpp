#ifndef token_hpp
#define token_hpp

#include <string>
#include <variant>
#include <functional>

/* TOKEN TYPE */
enum token_type
{
    NUMBER,
    REGISTER,
    MEMORY,
    LABEL,
    VAR,
    OPER,
    EXPRESSION,
    STRING,
    UNKNOWN
};

/* TOKEN VALUE TYPE */
enum token_value_type
{
    UNSIGNEDINT = 0,
    INT,
    FLOAT,
    CHAR,
    BOOL,
    NONE
};

using t_token_value = std::variant< unsigned int, int, double, char, bool >;

/**
 * @brief token_value class
 *  Use std::variant to support multiple types
 */
class token_value
{
public:
    token_value()
    {
        mType  = NONE;
        mValue = 0;
    }

    token_value( token_value_type type, t_token_value value )
    {
        mType  = type;
        mValue = value;
    }

    ~token_value() = default;

public:
    /**
     * @brief std::visit overload
     *  add two token_value
     */
    struct add_vister
    {
        token_value operator()( unsigned int& i, const unsigned int j ) const
        {
            unsigned int tmp = i + j;
            return token_value( UNSIGNEDINT, tmp );
        }
        token_value operator()( int& i, const int j ) const
        {
            int tmp = i + j;
            return token_value( INT, tmp );
        }
        token_value operator()( double& f, const double j ) const
        {
            double tmp = f + j;
            return token_value( FLOAT, tmp );
        }
        token_value operator()( char& c, const char j ) const
        {
            char tmp = c + j;
            return token_value( CHAR, tmp );
        }
        token_value operator()( bool& c, const bool j ) const { throw "bool can not add!"; }
    };

    /**
     * @brief std::visit overload
     *  subtract two token_value
     */
    struct sub_vister
    {
        token_value operator()( unsigned int& i, const unsigned int j ) const
        {
            unsigned int tmp = i - j;
            return token_value( UNSIGNEDINT, tmp );
        }
        token_value operator()( int& i, const int j ) const
        {
            int tmp = i - j;
            return token_value( INT, tmp );
        }
        token_value operator()( double& f, const double j ) const
        {
            double tmp = f - j;
            return token_value( FLOAT, tmp );
        }
        token_value operator()( char& c, const char j ) const
        {
            char tmp = c + j;
            return token_value( CHAR, tmp );
        }
        token_value operator()( bool& c, const bool j ) const { throw "bool can not sub!"; }
    };

    /**
     * @brief std::visit overload
     *  multiply two token_value
     */
    struct mul_vister
    {
        token_value operator()( unsigned int& i, const unsigned int j ) const
        {
            unsigned int tmp = i * j;
            return token_value( UNSIGNEDINT, tmp );
        }
        token_value operator()( int& i, const int j ) const
        {
            int tmp = i * j;
            return token_value( INT, tmp );
        }
        token_value operator()( double& f, const double j ) const
        {
            double tmp = f * j;
            return token_value( FLOAT, tmp );
        }
        token_value operator()( char& c, const char j ) const
        {
            char tmp = c * j;
            return token_value( CHAR, tmp );
        }
        token_value operator()( bool& c, const bool j ) const { throw "bool can not mul!"; }
    };

    /**
     * @brief std::visit overload
     *  Divide  two token_value
     */
    struct div_vister
    {
        token_value operator()( unsigned int& i, const unsigned int j ) const
        {
            unsigned int tmp = i / j;
            return token_value( UNSIGNEDINT, tmp );
        }
        token_value operator()( int& i, const int j ) const
        {
            int tmp = i / j;
            return token_value( INT, tmp );
        }
        token_value operator()( double& f, const double j ) const
        {
            double tmp = f / j;
            return token_value( FLOAT, tmp );
        }
        token_value operator()( char& c, const char j ) const
        {
            char tmp = c / j;
            return token_value( CHAR, tmp );
        }
        token_value operator()( bool& c, const bool j ) const { throw "bool can not div!"; }
    };

    /**
     * @brief left_shift_vister
     *  Move left action
     */
    struct left_shift_vister
    {
        token_value operator()( unsigned int& i, const int j ) const
        {
            unsigned int tmp = i << j;
            return token_value( UNSIGNEDINT, tmp );
        }
        token_value operator()( int& i, const int j ) const
        {
            int tmp = i << j;
            return token_value( INT, tmp );
        }
        token_value operator()( double& f, const int j ) const
        {
            throw "double can not left shift!";
        }
        token_value operator()( char& c, const char j ) const
        {
            char tmp = c << j;
            return token_value( CHAR, tmp );
        }
        token_value operator()( bool& c, const bool j ) const
        {
            throw "bool can not left shift!";
        }
    };

    /**
     * @brief right_shift_vister
     *  Move right action
     */
    struct right_shift_vister
    {
        token_value operator()( unsigned int& i, const int j ) const
        {
            unsigned int tmp = i >> j;
            return token_value( UNSIGNEDINT, tmp );
        }
        token_value operator()( int& i, const int j ) const
        {
            int tmp = i >> j;
            return token_value( INT, tmp );
        }
        token_value operator()( double& f, const int j ) const
        {
            throw "double can not left shift!";
        }
        token_value operator()( char& c, const char j ) const
        {
            char tmp = c >> j;
            return token_value( CHAR, tmp );
        }
        token_value operator()( bool& c, const bool j ) const
        {
            throw "bool can not right shift!";
        }
    };

    /**
     * @brief equal_cmp_Vister
     *  Whether the comparison is equal
     */
    struct equal_cmp_Vister
    {
        bool operator()( unsigned int& i, const int j ) const { return i == j; }
        bool operator()( int& i, const int j ) const { return i == j; }
        bool operator()( double& f, const int j ) const { return f == j; }
        bool operator()( char& c, const char j ) const { return c == j; }
        bool operator()( bool& c, const bool j ) const { return c == j; }
    };

    /**
     * @brief cmp_visiter
     *  Compare sizes
     */
    struct cmp_visiter
    {
        bool operator()( unsigned int& i, const int j ) const { return i > j; }
        bool operator()( int& i, const int j ) const { return i > j; }
        bool operator()( double& f, const int j ) const { return f > j; }
        bool operator()( char& c, const char j ) const { return c > j; }
        bool operator()( bool& c, const bool j ) const { return c > j; }
    };

public:
    /* -------------------------- Operator overloading ------------------------ */
    bool operator==( token_value other )
    {
        return std::visit( equal_cmp_Vister{}, mValue, other.mValue );
    }

    bool operator!=( token_value other )
    {
        if ( std::visit( equal_cmp_Vister{}, mValue, other.mValue ) )
        {
            return false;
        }
        return true;
    }

    bool operator>( token_value other )
    {
        return std::visit( cmp_visiter{}, mValue, other.mValue );
    }

    bool operator<( token_value other )
    {
        if ( std::visit( cmp_visiter{}, mValue, other.mValue ) )
        {
            return false;
        }
        return true;
    }

    token_value operator+( token_value other )
    {
        return std::visit( add_vister{}, mValue, other.mValue );
    }

    token_value operator-( token_value other )
    {
        return std::visit( sub_vister{}, mValue, other.mValue );
    }

    token_value operator*( token_value other )
    {
        return std::visit( mul_vister{}, mValue, other.mValue );
    }

    token_value operator/( token_value other )
    {
        return std::visit( div_vister{}, mValue, other.mValue );
    }

    token_value operator>>( token_value pos )
    {
        return std::visit( right_shift_vister{}, mValue, pos.mValue );
    }

    token_value operator<<( token_value pos )
    {
        return std::visit( left_shift_vister{}, mValue, pos.mValue );
    };

    void operator=( token_value other )
    {
        mType  = other.mType;
        mValue = other.mValue;
    }

    token_value_type mType;

    t_token_value mValue;
};

/**
 * @brief token struct
 *
 */
struct token
{
    std::string name;
    token_value value;
    token_type type;
};

/* ---------------- Initialize different types of tokens ------------------- */

#define NONE_TYPE_TOKEN() token_value()

#define INT_VALUE( val ) token_value( INT, ( int )val )

#define UINT_VALUE( val ) token_value( UNSIGNEDINT, ( unsigned int )val )

#define FLOAT_VALUE( val ) token_value( FLOAT, ( double )val )

#define CHAR_VALUE( val ) token_value( CHAR, ( char )val )

#define BOOL_VALUE( val ) token_value( BOOL, ( bool )val )

/*----------------------- Get the values of different types of tokens ---------------------------*/

#define GET_INT_VALUE( int_value ) std::get< int >( int_value.mValue )

#define GET_UINT_VALUE( uint_value ) std::get< unsigned int >( uint_value.mValue )

#define GET_FLOAT_VALUE( float_value ) std::get< double >( float_value.mValue )

#define GET_CHAR_VALUE( char_value ) std::get< char >( char_value.mValue )

#define GET_BOOL_VALUE( bool_value ) std::get< bool >( bool_value.mValue )

#endif
