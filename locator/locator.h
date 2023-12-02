//
// Created by ghitsh on 02.12.23.
//

#ifndef LOCATOR_LOCATOR_H
#define LOCATOR_LOCATOR_H


#include "zone.h"
#include "subscriber.h"

#include <map>
#include <string>
#include <list>


class Locator
{
public:
	Locator();



private:
	std::map<std::string, Subscriber*> subscribers;
	std::map<unsigned, Zone*> zones;
	std::map<std::string, std::list<Zone*>> zone_subscribers;
	std::map<unsigned, std::list<Subscriber*>> subscriber_zones;
};


#endif //LOCATOR_LOCATOR_H
