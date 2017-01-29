/*
 * main.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Luke
 */

#include "HueBridge.h"

#include <unistd.h>
#include <iostream>
#include <thread>

#define	QUIT_COMMAND "q"

bool mQNotPressed = true;
bool mUpdateStepReached = false;


void philipsBridgeInterfaceThread()
{
	HueBridge tHueBridge;

	// Run while address invalid and q not pressed
	std::string tAddress;
	std::string tUser;

	// Ask user for address of bridge
	std::cout << "\nWelcome to Philip's Hue State Reader!" << std::endl;
	std::cout << "Please enter your Philip's Bridge Address: ";
	std::cin >> tAddress;

	std::cout << "Please enter your Philip's Bridge Username: ";
	std::cin >> tUser;
	std::cout << std::endl;

	// Configure Bridge API to use given address and check address'/username's validity
	if (tHueBridge.connect(tAddress, tUser) == true)
	{
		std::cout << "** Error validating username or address, please restart program and try again";
		mQNotPressed = false;
		return;
	}

	mUpdateStepReached = true;
	std::cout << "Connection to bridge '" << tHueBridge.getBridgeName() << "' successful!" << std::endl;
	std::cout << "Enter '" << QUIT_COMMAND << "' to exit at any time\n" << std::endl;

	// Get all lights and add to list
	tHueBridge.getLights();

	// Run until user issues exit command
	while (mQNotPressed)
	{
		tHueBridge.updateLights();
		usleep(1000000); // 1sh
	}
}


int main(int argc, char *argv[])
{
	// Start Philips interface thread
	std::thread tInterfaceThread(philipsBridgeInterfaceThread);

	// Wait for q to be pressed for exit
	while (mQNotPressed)
	{
		if (mUpdateStepReached == false) continue;
		if (std::cin.get() == 'q') mQNotPressed = false;
	}

	std::cout << "\n\nProgram Complete!\n" << std::endl;
    return 0;
}

