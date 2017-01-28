/*
 * HueBridge.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Luke
 */

#ifndef HUEBRIDGE_H_
#define HUEBRIDGE_H_

#include "PhillipsHueLight.h"

#include <rapidjson/Document.h>

#include <string>
#include <map>

typedef std::map<std::string, PhillipsHueLight*> LightMap;

class HueBridge
{

public:

	HueBridge();
	~HueBridge();

	bool setAddress(std::string iAddress);
	const std::string getAddress();

	bool getLights();
	void updateLights();

private:

	std::string mAddress;
	LightMap mLightMap;

	void addLight(std::string iId);
	void updateLight(PhillipsHueLight* iLight);
	void checkLights();

	rapidjson::Document* makeHttpRequest(std::string iKey);

	void printAllLights();
	void printNewLight(PhillipsHueLight* iLight, bool iLastLight, bool iTabbed);

};

#endif /* HUEBRIDGE_H_ */
