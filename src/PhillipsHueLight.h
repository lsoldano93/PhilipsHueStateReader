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

	void setId(int iId);
	const int getId() const;

	void setName(std::string iName);
	const std::string getName() const;

	void setState(bool iState);
	const bool getState() const;

	void setBrightness(int iBrightness);
	const int getBrightness() const;

private:

	int mId;
	std::string mName;
	bool mLightOn;
	int mBrightness;



};

#endif /* PHILLIPSHUELIGHT_H_ */
