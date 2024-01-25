//
// Created by ghitsh on 04.12.23.
//

#ifndef LOCATOR_ZONE_TRIGGER_H
#define LOCATOR_ZONE_TRIGGER_H


#include <string>

#include <spdlog/spdlog.h>


enum Event {ENTERING_ZONE, EXITING_ZONE, ENTERING_EXITING_ZONE};


class ZoneTrigger
{
public:
	ZoneTrigger(std::string const&, std::string const&, unsigned, Event);

	std::string const& get_id() const;

	unsigned get_zone_id() const;

	std::string const& get_subscriber_id() const;

	Event get_event_type() const;

	void action() const;

private:
	std::string id;
	unsigned zone_id;
	std::string subscriber_id;
	Event event;
};


#endif //LOCATOR_ZONE_TRIGGER_H
