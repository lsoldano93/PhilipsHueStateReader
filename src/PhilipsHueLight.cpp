/*
 * PhilipsHueLight.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Luke
 */

#include "constants.h"
#include "PhilipsHueLight.h"

#include <iostream>



PhilipsHueLight::PhilipsHueLight(std::string iId, std::string iName, bool iLightOn, int iBrightness)
{
	mId = iId;
	mName = iName;
	mLightOn = iLightOn;
	mBrightness = iBrightness;
}


PhilipsHueLight::~PhilipsHueLight()
{

}


// Note that iBrightness will be on a scale of 0 to MAX_BRIGHTNESS (provided by Hue API) instead of 0 to 100% (as it is printed out)
//PhilipsHueLight* PhilipsHueLight::CreateLight(std::string iId, std::string iName, bool iLightOn, int iBrightness)
//{
//	if (iBrightness < 0 || iBrightness > MAX_BRIGHTNESS) return 0;
//
//	return new PhilipsHueLight(iId, iName, iLightOn, iBrightness);
//}


const std::string PhilipsHueLight::getId() const
{
	return mId;
}


// Takes in new value and prints update
void PhilipsHueLight::setName(std::string iName)
{
	mName = iName;
	printChange(NAME_PRINT_KEY, iName);
}


const std::string PhilipsHueLight::getName() const
{
	return mName;
}


// Takes in new value and prints update
void PhilipsHueLight::setState(bool iState)
{
	mLightOn = iState;
	printChange(LIGHT_STATE_PRINT_KEY, iState);
}


const bool PhilipsHueLight::getState() const
{
	return mLightOn;
}


// Takes in new value and prints update
void PhilipsHueLight::setBrightness(int iBrightness)
{
	mBrightness = iBrightness;
	if (iBrightness < 0 || iBrightness > MAX_BRIGHTNESS) printChange(BRIGHTNESS_PRINT_KEY, 0, true);
	else printChange(BRIGHTNESS_PRINT_KEY, getPercentBrightness(), false);
}


const int PhilipsHueLight::getBrightness() const
{
	return mBrightness;
}


const int PhilipsHueLight::getPercentBrightness() const
{
	return ((100 * mBrightness) / MAX_BRIGHTNESS);
}


void PhilipsHueLight::printChange(std::string iKey, std::string iNewValue)
{
	std::cout << "{" << std::endl;
	std::cout << "\t\"" << ID_PRINT_KEY << "\": \"" << mId << "\"," << std::endl;
	std::cout << "\t\"" << iKey << "\": \"" << iNewValue << "\"" << std::endl;
	std::cout << "}" << std::endl;
}


void PhilipsHueLight::printChange(std::string iKey, bool iNewValue)
{
	std::cout << "{" << std::endl;
	std::cout << "\t\"" << ID_PRINT_KEY << "\": \"" << mId << "\"," << std::endl;
	std::cout << "\t\"" << iKey << "\": " << (iNewValue ? "true" : "false") << std::endl;
	std::cout << "}" << std::endl;
}


void PhilipsHueLight::printChange(std::string iKey, int iNewValue, bool iInvalidValue)
{
	std::cout << "{" << std::endl;
	std::cout << "\t\"" << ID_PRINT_KEY << "\": \"" << mId << "\"," << std::endl;
	std::cout << "\t\"" << iKey << "\": " << (iInvalidValue ? "invalid" : std::to_string(iNewValue)) << std::endl;
	std::cout << "}" << std::endl;
}


