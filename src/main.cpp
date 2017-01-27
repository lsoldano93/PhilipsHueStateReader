/*
 * main.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Luke
 */


#include <iostream>
//#include <curl/curl.h>
//#include <curlpp/cURLpp.hpp>

int main(int argc, char *argv[])
{
    std::string tIpAddress;

    std::cout << "Welcome to Phillip's Hue State Reader!\n";
    std::cout << "Please enter your Phillip's Bridge IP Address: ";

    std::cin >> tIpAddress;
    std::cout << "IP Address: " << tIpAddress << "\n";

    return 0;
}

