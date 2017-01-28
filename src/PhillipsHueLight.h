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

	static PhillipsHueLight* CreateLight(std::string iId, std::string iName, bool iLightOn, int iBrightness);
	~PhillipsHueLight();

	const std::string getId() const;

	void setName(std::string iName);
	const std::string getName() const;

	void setState(bool iState);
	const bool getState() const;

	void setBrightness(int iBrightness);
	const int getBrightness() const;


private:

	std::string mId;
	std::string mName;
	bool mLightOn;
	int mBrightness;

	PhillipsHueLight();
	PhillipsHueLight(std::string iId, std::string iName, bool iLightOn, int iBrightness);

	void printChange(std::string iKey, std::string iNewValue);
	void printChange(std::string iKey, bool iNewValue);
	void printChange(std::string iKey, int iNewValue);

};

#endif /* PHILLIPSHUELIGHT_H_ */
