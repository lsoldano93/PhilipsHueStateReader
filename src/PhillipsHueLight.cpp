/*
 * PhillipsHueLight.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Luke
 */

#include "constants.h"
#include "PhillipsHueLight.h"


PhillipsHueLight::PhillipsHueLight()
{
	// TODO Auto-generated constructor stub
}


PhillipsHueLight::PhillipsHueLight(int iId, std::string iName, bool iLightOn, int iBrightness)
{
	mId = iId;
	mName = iName;
	mLightOn = iLightOn;
	mBrightness = (100 * iBrightness) / MAX_BRIGHTNESS;
}


PhillipsHueLight::~PhillipsHueLight()
{
	// TODO Auto-generated destructor stub
}


// Note that iBrightness will be on a scale of 0 to MAX_BRIGHTNESS (provided by Hue API) instead of 0 to 100
PhillipsHueLight* PhillipsHueLight::CreateLight(int iId, std::string iName, bool iLightOn, int iBrightness)
{
	if (iId < 0) return 0;
	if (iBrightness < 0 || iBrightness > MAX_BRIGHTNESS) return 0;

	return new PhillipsHueLight(iId, iName, iLightOn, iBrightness);
}


const int PhillipsHueLight::getId() const
{
	return mId;
}


const std::string PhillipsHueLight::getName() const
{
	return mName;
}


const bool PhillipsHueLight::getState() const
{
	return mLightOn;
}


const int PhillipsHueLight::getBrightness() const
{
	return mBrightness;
}


