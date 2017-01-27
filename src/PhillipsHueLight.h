/*
 * PhillipsHueLight.h
 *
 *  Created on: Jan 26, 2017
 *      Author: Luke
 */

#ifndef PHILLIPSHUELIGHT_H_
#define PHILLIPSHUELIGHT_H_

#include <string>

class PhillipsHueLight
{

public:

	PhillipsHueLight();
	PhillipsHueLight(int iId, std::string iName, bool iLightOn, int iBrightness);
	~PhillipsHueLight();

	static PhillipsHueLight* CreateLight(int iId, std::string iName, bool iLightOn, int iBrightness);

	const int getId() const;
	const std::string getName() const;
	const bool getState() const;
	const int getBrightness() const;

private:

	int mId;
	std::string mName;
	bool mLightOn;
	int mBrightness;



};

#endif /* PHILLIPSHUELIGHT_H_ */
