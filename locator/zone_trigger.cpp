//
// Created by ghitsh on 04.12.23.
//

#include "zone_trigger.h"

#include <utility>

ZoneTrigger::ZoneTrigger(std::string id, std::string subscriber_id, unsigned zone_id, Event event) :
	id(std::move(id)),
	zone_id(zone_id),
	subscriber_id(std::move(subscriber_id)),
	event(event)
{}

std::string const& ZoneTrigger::get_id() const
{
	return id;
}

unsigned ZoneTrigger::get_zone_id() const
{
	return zone_id;
}

std::string const& ZoneTrigger::get_subscriber_id() const
{
	return subscriber_id;
}

Event ZoneTrigger::get_event_type() const
{
	return event;
}

void ZoneTrigger::action() const
{
	// entered
	// left
	std::string event_type;
	switch (event) {
		case Event::ENTERING_ZONE:
			event_type = "entered";
			break;
		case Event::EXITING_ZONE:
			event_type = "left";
			break;
		case Event::ENTERING_EXITING_ZONE:
			event_type = "entered/left";
			break;
	}
	std::string msg = "The subscriber with id '" + subscriber_id + "' has just " + event_type + " the zone with id " + std::to_string(zone_id) + ".";
	spdlog::info(msg);
}

