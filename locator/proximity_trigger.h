//
// Created by ghitsh on 04.12.23.
//

#ifndef LOCATOR_PROXIMITY_TRIGGER_H
#define LOCATOR_PROXIMITY_TRIGGER_H


#include <string>

#include <spdlog/spdlog.h>


class ProximityTrigger
{
public:
	ProximityTrigger(std::string const& id,
			 std::string const& first_subscriber_id,
			 std::string const& second_subscriber_id,
	                 unsigned int distance);

	std::string const& get_id() const;

	std::string const& get_first_subscriber_id() const;

	std::string const& get_second_subscriber_id() const;

	unsigned get_distance() const;

	void action() const;

private:
	std::string id;
	std::string first_subscriber_id;
	std::string second_subscriber_id;
	unsigned distance;
};


#endif //LOCATOR_PROXIMITY_TRIGGER_H
