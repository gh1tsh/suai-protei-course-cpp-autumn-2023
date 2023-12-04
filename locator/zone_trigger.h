//
// Created by ghitsh on 04.12.23.
//

#ifndef LOCATOR_ZONE_TRIGGER_H
#define LOCATOR_ZONE_TRIGGER_H


#include "subscriber.h"
#include "zone.h"

#include <string>

#include <spdlog/spdlog.h>


enum Event {ENTERING_ZONE, EXITING_ZONE, ENTERING_EXITING_ZONE};


class ZoneTrigger
{
public:
	ZoneTrigger(std::string , unsigned, std::string , Event);

private:
	std::string id;
	unsigned zone_id;
	std::string subscriber_id;
	Event event;
};


#endif //LOCATOR_ZONE_TRIGGER_H
