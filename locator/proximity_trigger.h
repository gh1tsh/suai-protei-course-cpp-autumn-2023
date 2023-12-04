//
// Created by ghitsh on 04.12.23.
//

#ifndef LOCATOR_PROXIMITY_TRIGGER_H
#define LOCATOR_PROXIMITY_TRIGGER_H


#include "subscriber.h"

#include <string>

#include <spdlog/spdlog.h>


class ProximityTrigger
{
public:
	ProximityTrigger(std::string  id, std::string  first_subscriber_id, std::string  second_subscriber_id,
	                 unsigned int distance);

	void action() const;

private:
	std::string id;
	std::string first_subscriber_id;
	std::string second_subscriber_id;
	unsigned distance;
};


#endif //LOCATOR_PROXIMITY_TRIGGER_H
