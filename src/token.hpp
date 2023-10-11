#ifndef token_hpp
#define token_hpp

#include <string>

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

struct token
{
    std::string name;
    unsigned int value;
    token_type type;
};

#endif
