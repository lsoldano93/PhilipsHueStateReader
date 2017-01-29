/*
 * PhilipsHueLight.h
 *
 *  Created on: Jan 26, 2017
 *      Author: Luke
 */

#ifndef PHILIPSHUELIGHT_H_
#define PHILIPSHUELIGHT_H_

#include <string>

class PhilipsHueLight
{

public:

	static PhilipsHueLight* CreateLight(std::string iId, std::string iName, bool iLightOn, int iBrightness);
	~PhilipsHueLight();

	const std::string getId() const;

	void setName(std::string iName);
	const std::string getName() const;

	void setState(bool iState);
	const bool getState() const;

	void setBrightness(int iBrightness);
	const int getBrightness() const;
	const int getPercentBrightness() const;


private:

	std::string mId;
	std::string mName;
	bool mLightOn;
	int mBrightness;

	PhilipsHueLight();
	PhilipsHueLight(std::string iId, std::string iName, bool iLightOn, int iBrightness);

	void printChange(std::string iKey, std::string iNewValue);
	void printChange(std::string iKey, bool iNewValue);
	void printChange(std::string iKey, int iNewValue);

};

#endif /* PHILIPSHUELIGHT_H_ */
