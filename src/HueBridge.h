/*
 * HueBridge.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Luke
 */

#ifndef HUEBRIDGE_H_
#define HUEBRIDGE_H_

#include "PhilipsHueLight.h"

#include <rapidjson/Document.h>

#include <string>
#include <map>

typedef std::map<std::string, PhilipsHueLight*> LightMap;

class HueBridge
{

public:

	HueBridge();
	~HueBridge();

	void setUser(std::string iUser);
	bool setAddress(std::string iAddress);
	const std::string getAddress();

	bool getLights();
	void updateLights();

private:

	std::string mUser;
	std::string mAddress;
	LightMap mLightMap;

	void addOrUpdateLight(bool iNewLight, std::string iId, PhilipsHueLight* iLightToUpdate);
	void addOrUpdateLight(rapidjson::Value::ConstMemberIterator iLightIt, bool iNewLight, PhilipsHueLight* iLightToUpdate);
	void checkLights();

	rapidjson::Document* makeHttpRequest(std::string iKey);

	void printAllLights();
	void printNewLight(PhilipsHueLight* iLight, bool iLastLight, bool iTabbed);

};

#endif /* HUEBRIDGE_H_ */
