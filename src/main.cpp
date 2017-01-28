/*
 * main.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Luke
 */

#include "HueBridge.h"

#include <unistd.h>
#include <iostream>


int main(int argc, char *argv[])
{
	HueBridge tHueBridge;

    // TODO: Add ability to exit with key press
    // Run while address invalid
    while (true)
    {
    	std::string tAddress;

		// Ask user for address of bridge
		std::cout << "Welcome to Phillip's Hue State Reader!" << std::endl;
		std::cout << "Please enter your Phillip's Bridge IP Address: ";
		//std::cin >> tAddress;
		std::cout << std::endl;

		// Configure Bridge API to use given address and check address' validity
		tAddress = "localhost";
		if (tHueBridge.setAddress(tAddress) == false) break;
    }

    // Get all lights and add to list
    tHueBridge.getLights();

    // TODO: Add ability to exit with key press
    // Run until user issues exit command
    while (true)
    {
    	tHueBridge.updateLights();
    	usleep(1000000);
    }

    return 0;
}

