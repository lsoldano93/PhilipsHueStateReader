
#include <iostream>


int main(int argc, char *argv[])
{
    std::string tIpAddress;

    std::cout << "Welcome to Phillips Hue State Reader!\n";
    std::cout << "Please enter your Phillip's Bridge IP Address: ";

    std::cin >> tIpAddress;
    std::cout << "IP Address: " << tIpAddress << "\n";

    return 0;
}
