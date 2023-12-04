//
// Created by ghitsh on 04.12.23.
//

#include "zone_trigger.h"

#include <utility>

ZoneTrigger::ZoneTrigger(std::string  id, unsigned zone_id, std::string  subscriber_id, Event event) :
	id(std::move(id)),
	zone_id(zone_id),
	subscriber_id(std::move(subscriber_id)),
	event(event)
{}
