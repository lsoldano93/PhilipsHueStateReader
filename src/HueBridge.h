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
#include <list>


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
	std::list<PhillipsHueLight*> mLightsList;

	rapidjson::Document* makeHttpRequest(std::string iKey);

	void printAllLights();

};

#endif /* HUEBRIDGE_H_ */
