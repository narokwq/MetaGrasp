//
// Created by Alex on 23/02/2017.
//

#include "Util.h"

std::vector<std::string> Util::explode(const std::string& argsString, const char& caractere)
{
    std::string buff{""};
    std::vector<std::string> vetorString;

    for(auto elemento:argsString)
    {
        if(elemento != caractere) buff+=elemento; else
        if(elemento == caractere && buff != "") { vetorString.push_back(buff); buff = ""; }
    }
    if(buff != "") vetorString.push_back(buff);

    return vetorString;
}