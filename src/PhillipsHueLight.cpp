/*
 * PhillipsHueLight.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Luke
 */

#include "constants.h"
#include "PhillipsHueLight.h"

#include <iostream>


PhillipsHueLight::PhillipsHueLight()
{

}


PhillipsHueLight::PhillipsHueLight(std::string iId, std::string iName, bool iLightOn, int iBrightness)
{
	mId = iId;
	mName = iName;
	mLightOn = iLightOn;
	mBrightness = iBrightness;
}


PhillipsHueLight::~PhillipsHueLight()
{

}


// Note that iBrightness will be on a scale of 0 to MAX_BRIGHTNESS (provided by Hue API) instead of 0 to 100% (as it is printed out)
PhillipsHueLight* PhillipsHueLight::CreateLight(std::string iId, std::string iName, bool iLightOn, int iBrightness)
{
	if (iBrightness < 0 || iBrightness > MAX_BRIGHTNESS) return 0;

	return new PhillipsHueLight(iId, iName, iLightOn, iBrightness);
}


const std::string PhillipsHueLight::getId() const
{
	return mId;
}


// Takes in new value and prints update
void PhillipsHueLight::setName(std::string iName)
{
	mName = iName;
	printChange(NAME_PRINT_KEY, iName);
}


const std::string PhillipsHueLight::getName() const
{
	return mName;
}


// Takes in new value and prints update
void PhillipsHueLight::setState(bool iState)
{
	mLightOn = iState;
	printChange(LIGHT_STATE_PRINT_KEY, iState);
}


const bool PhillipsHueLight::getState() const
{
	return mLightOn;
}


// Takes in new value and prints update
void PhillipsHueLight::setBrightness(int iBrightness)
{
	mBrightness = iBrightness;
	printChange(BRIGHTNESS_PRINT_KEY, getPercentBrightness());
}


const int PhillipsHueLight::getBrightness() const
{
	return mBrightness;
}


const int PhillipsHueLight::getPercentBrightness() const
{
	return (100 * mBrightness) / MAX_BRIGHTNESS;
}


void PhillipsHueLight::printChange(std::string iKey, std::string iNewValue)
{
	std::cout << "{" << std::endl;
	std::cout << "\t\"" << ID_PRINT_KEY << "\": \"" << mId << "\"," << std::endl;
	std::cout << "\t\"" << iKey << "\": \"" << iNewValue << "\"" << std::endl;
	std::cout << "}" << std::endl;
}


void PhillipsHueLight::printChange(std::string iKey, bool iNewValue)
{
	std::cout << "{" << std::endl;
	std::cout << "\t\"" << ID_PRINT_KEY << "\": \"" << mId << "\"," << std::endl;
	std::cout << "\t\"" << iKey << "\": " << (iNewValue ? "true" : "false") << std::endl;
	std::cout << "}" << std::endl;
}


void PhillipsHueLight::printChange(std::string iKey, int iNewValue)
{
	std::cout << "{" << std::endl;
	std::cout << "\t\"" << ID_PRINT_KEY << "\": \"" << mId << "\"," << std::endl;
	std::cout << "\t\"" << iKey << "\": " << iNewValue << std::endl;
	std::cout << "}" << std::endl;
}


