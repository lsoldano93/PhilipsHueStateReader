/*
 * HueBridge.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: Luke
 */

#include "constants.h"
#include "HueBridge.h"

//#include <sstream>
#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>


HueBridge::HueBridge()
{

}


HueBridge::~HueBridge()
{

}


bool HueBridge::setAddress(std::string iAddress)
{
	// TODO: Check iAddress

	mAddress = iAddress;

	return false;
}


const std::string HueBridge::getAddress()
{
	return mAddress;
}


bool HueBridge::getLights()
{
	makeHttpRequest(NEW_DEVELOPER_KEY);
}


// Checks for new lights, then checks lights in given list and updates their state
void HueBridge::updateLights()
{

}


// Uses cURLpp to make HTTP request to Hue Bridge
void HueBridge::makeHttpRequest(std::string iKey)
{
	// Reformat to include Bridge address
	std::string tUrl = mAddress + "/" + iKey;
	std::cout << "Making request to " << tUrl << "\n"; // TODO Remove

	try
	{
		// All that is required for clean up
		curlpp::Cleanup tCleanup;

		// Configure request
		curlpp::Easy tRequest;
		tRequest.setOpt(curlpp::options::Url(tUrl));
		tRequest.setOpt(curlpp::options::Timeout(1));

		tRequest.perform();


	}
	catch( curlpp::RuntimeError &e )
	{
		std::cout << e.what() << "\n";
	}

	catch( curlpp::LogicError &e )
	{
		std::cout << e.what() << "\n";
	}

	std::cout << "\n";

}





