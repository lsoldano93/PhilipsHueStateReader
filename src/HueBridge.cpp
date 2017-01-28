/*
 * HueBridge.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: Luke
 */

#include "constants.h"
#include "HueBridge.h"

#include <sstream>
#include <iostream>
#include <set>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>


HueBridge::HueBridge()
{

}


HueBridge::~HueBridge()
{
	// Free PhillipsHueLights pointers
	for (auto tIt : mLightMap) delete tIt.second;
}


bool HueBridge::setAddress(std::string iAddress)
{
	// TODO: Check iAddress

	mAddress = iAddress;

	return false;
}


const std::string HueBridge::getAddress()
{
	return mAddress;
}


bool HueBridge::getLights()
{
	rapidjson::Document* tJson = makeHttpRequest(GET_FULL_STATE_KEY);

	// Verify JSON object
	if (tJson == 0 || tJson->IsObject() == false)
	{
		std::cout << "** Error in request/response string at getLights()\n";
		delete tJson;
		return true;
	}

	// Check for Lights key
	if (tJson->HasMember(LIGHTS_JSON_KEY) == false || (*tJson)[LIGHTS_JSON_KEY].IsObject() == false)
	{
		std::cout << "** Error with LIGHTS_KEY at getLights()\n";
		delete tJson;
		return true;
	}

	// Iterate through JSON lights object
	for (auto tLight = (*tJson)[LIGHTS_JSON_KEY].MemberBegin(); tLight != (*tJson)[LIGHTS_JSON_KEY].MemberEnd(); ++tLight)
	{
		// Get light id
		std::string tId = tLight->name.GetString();

		// Get state values
		if (tLight->value.HasMember(STATE_JSON_KEY) == false)
		{
			std::cout << "** Error with STATE_KEY for " << tId << " at getLights()\n";
			continue;
		}


		//// Get light state
		if (tLight->value[STATE_JSON_KEY].HasMember(LIGHT_STATE_JSON_KEY) == false)
		{
			std::cout << "** Error with LIGHT_STATE_KEY for " << tId << " at getLights()\n";
			continue;
		}

		bool tLightState = tLight->value[STATE_JSON_KEY][LIGHT_STATE_JSON_KEY].GetBool();


		//// Get brightness
		if (tLight->value[STATE_JSON_KEY].HasMember(BRIGHTNESS_JSON_KEY) == false)
		{
			std::cout << "** Error with BRIGHTNESS_KEY for " << tId << " at getLights()\n";
			continue;
		}

		int tBrightness = tLight->value[STATE_JSON_KEY][BRIGHTNESS_JSON_KEY].GetInt();


		// Get name
		if (tLight->value.HasMember(NAME_JSON_KEY) == false)
		{
			std::cout << "** Error with NAME_KEY for " << tId << " at getLights()\n";
			continue;
		}

		std::string tName = tLight->value[NAME_JSON_KEY].GetString();


		// Create a new Phillips Hue Light and store if it meets criteria
		PhillipsHueLight* tHueLight = PhillipsHueLight::CreateLight(tId, tName, tLightState, tBrightness);
		if (tHueLight != 0) mLightMap[tId] = tHueLight;
	}

	printAllLights();
	delete tJson;
	return false;
}


// Checks for new lights, then checks lights in member map and updates their state
void HueBridge::updateLights()
{
	checkLights();
	for (auto it : mLightMap) updateLight(it.second);
}


// Checks light listing for new lights and removed lights
void HueBridge::checkLights()
{
	// Get lights list, push light ids to stack
	rapidjson::Document* tJson = makeHttpRequest(GET_LIGHTS_KEY);

	// Verify JSON object
	if (tJson == 0 || tJson->IsObject() == false)
	{
		std::cout << "** Error in request/response string at checkLights()\n";
		delete tJson;
		return;
	}


	// Iterate through JSON object
	std::set<std::string> tLightIds;
	for (auto tIt = tJson->MemberBegin(); tIt != tJson->MemberEnd(); ++tIt)
	{
		tLightIds.insert(tIt->name.GetString());
	}


	// Compare ids to map - add new lights
	for (const auto& tIt : tLightIds)
	{
		const auto tIt2 = mLightMap.find(tIt);
		if (tIt2 == mLightMap.end()) addLight(tIt);
	}


	// Compare ids to map - remove old lights
	for (auto tIt = mLightMap.begin(); tIt != mLightMap.end(); )
	{
		const auto tIt2 = tLightIds.find(tIt->first);
		if (tIt2 == tLightIds.end()) delete tIt->second;
		mLightMap.erase(tIt++);
	}
}


// Adds a new light to member map
void HueBridge::addLight(std::string iId)
{

}


// Updates a given light
void HueBridge::updateLight(PhillipsHueLight* iLight)
{

}


// Uses cURLpp to make HTTP request to Hue Bridge
rapidjson::Document* HueBridge::makeHttpRequest(std::string iKey)
{
	// Reformat to include Bridge address
	std::string tUrl = mAddress + "/" + iKey;

#if DEBUG
	std::cout << "Making request to " << tUrl << "\n";
#endif

	try
	{
		// All that is required for clean up
		curlpp::Cleanup tCleanup;

		// Configure request
		curlpp::Easy tRequest;
		std::ostringstream tResponseStream;
		curlpp::options::WriteStream tWs(&tResponseStream);

		tRequest.setOpt(curlpp::options::Url(tUrl));
		tRequest.setOpt(curlpp::options::Timeout(1));
		tRequest.setOpt(tWs);

		tRequest.perform();

#if DEBUG
		std::cout << "Response: " << tResponseStream.str() << "\n";
#endif

		// Format to JSON and check for error
		rapidjson::Document* tJson = new rapidjson::Document;
		if (tJson->Parse(tResponseStream.str().c_str()).HasParseError())
		{
			delete tJson;
			return 0;
		}

#if DEBUG
	for (auto tIt = tJson->MemberBegin(); tIt != tJson->MemberEnd(); ++tIt)
	{
		static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
		printf("Type of member %s is %s\n", tIt->name.GetString(), kTypeNames[tIt->value.GetType()]);
	}
#endif

		return tJson;
	}
	catch( curlpp::RuntimeError &e )
	{
		std::cout << e.what() << "\n";
	}

	catch( curlpp::LogicError &e )
	{
		std::cout << e.what() << "\n";
	}

	return 0;
}


// Prints all member lights in a JSON object format
void HueBridge::printAllLights()
{
	std::cout << "{" << std::endl;

	auto tIt = mLightMap.begin();
	for ( ; tIt != mLightMap.end(); ) printNewLight((*tIt).second, ++tIt == mLightMap.end(), true);

	std::cout << "}" << std::endl;
}


// Can be used to print an individual new light (Light, True, False) or a set of lights in a JSON object (Light#x, #x==#last, True)
void HueBridge::printNewLight(PhillipsHueLight* iLight, bool iLastLight, bool iTabbed)
{
	std::cout << (iTabbed ? "\t" : "") << "{" << std::endl;
	std::cout << "\t" << (iTabbed ? "\t" : "") << "\"" << NAME_PRINT_KEY << "\": \"" << iLight->getName() << "\"," << std::endl;
	std::cout << "\t" << (iTabbed ? "\t" : "") << "\"" << ID_PRINT_KEY << "\": \"" << iLight->getId() << "\"," << std::endl;
	std::cout << "\t" << (iTabbed ? "\t" : "") << "\"" << LIGHT_STATE_PRINT_KEY << "\": " << (iLight->getState() ? "true" : "false") << std::endl;
	std::cout << "\t" << (iTabbed ? "\t" : "") << "\"" << BRIGHTNESS_PRINT_KEY << "\": " << iLight->getBrightness() << std::endl;
	std::cout << (iTabbed ? "\t" : "") << "}" << (iLastLight ? "" : ",") << std::endl;
}



