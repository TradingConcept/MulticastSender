#ifndef HELPERS_HPP_INCLUDED
#define HELPERS_HPP_INCLUDED

#include <string>

class Helpers
{
public:

    static unsigned char* base64_decode(const std::string &in) ;

    static long GetSecuenciaBiva(const unsigned char* in);
    static long GetSecuenciaBmv(const unsigned char* in);
};

#endif // HELPERS_HPP_INCLUDED
