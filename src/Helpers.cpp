#include "Helpers.hpp"
#include <vector>
#include <iostream>

unsigned char* Helpers::base64_decode(const std::string &in) {

    int in_size = in.length() * 6 / 8 ;
    auto out = new unsigned char[in_size];

    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    int val=0, valb=-8, i = 0 ;
    for (auto c : in) {
        if (T[c] == -1) break;
        val = (val<<6) + T[c];
        valb += 6;
        if (valb>=0) {
            out[i++] = char((val>>valb)&0xFF);
            valb-=8;
        }
    }
    return out;
}

long Helpers::GetSecuenciaBiva(const unsigned char* in)
{
    long t_num = *((long*) &in);
    return t_num ;
}

long Helpers::GetSecuenciaBmv(const unsigned char* in)
{
    long t_num = *(((int*) in));
    return t_num ;
}

