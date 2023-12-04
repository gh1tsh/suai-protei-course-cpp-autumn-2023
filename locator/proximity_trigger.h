//
// Created by ghitsh on 04.12.23.
//

#ifndef LOCATOR_PROXIMITY_TRIGGER_H
#define LOCATOR_PROXIMITY_TRIGGER_H


#include "subscriber.h"

#include <string>


class ProximityTrigger
{
public:
	ProximityTrigger(std::string  id, std::string  firstSubscriberId, std::string  secondSubscriberId,
	                 unsigned int distance);

private:
	std::string id;
	std::string first_subscriber_id;
	std::string second_subscriber_id;
	unsigned distance;
};


#endif //LOCATOR_PROXIMITY_TRIGGER_H
