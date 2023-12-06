//
// Created by ghitsh on 04.12.23.
//

#include "zone_trigger.h"

#include <utility>
#include <exception>

ZoneTrigger::ZoneTrigger(std::string const& id, std::string const& subscriber_id, unsigned zone_id, Event event) :
	zone_id(zone_id),
	event(event)
{
	if (id.empty()) {
		throw std::invalid_argument("ZoneTrigger identifier cannot be empty string.");
	} else {
		this->id = id;
	}

	if (subscriber_id.empty()) {
		throw std::invalid_argument("Subscriber identifier cannot be empty string.");
	} else {
		this->subscriber_id = subscriber_id;
	}
}

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
//	std::string event_type;
//	switch (event) {
//		case Event::ENTERING_ZONE:
//			event_type = "entered";
//			break;
//		case Event::EXITING_ZONE:
//			event_type = "left";
//			break;
//		case Event::ENTERING_EXITING_ZONE:
//			event_type = "entered/left";
//			break;
//	}
//	std::string msg = "The subscriber with id '" + subscriber_id + "' has just " + event_type + " the zone with id " + std::to_string(zone_id) + ".";
//	spdlog::info(msg);

	std::string msg = "Zone " + std::to_string(zone_id) + " trigger!";
	spdlog::info(msg);
}

