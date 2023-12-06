//
// Created by ghitsh on 04.12.23.
//

#include "proximity_trigger.h"

#include <utility>
#include <exception>

ProximityTrigger::ProximityTrigger(std::string const& id,
				   std::string const& first_subscriber_id,
				   std::string const& second_subscriber_id,
				   unsigned distance)
{
	if (id.empty()) {
		throw std::invalid_argument("ProximityTrigger identifier cannot be empty string.");
	} else {
		this->id = id;
	}
	if (first_subscriber_id.empty() || second_subscriber_id.empty()) {
		throw std::invalid_argument("Subscriber identifier cannot be empty string.");
	} else {
		this->first_subscriber_id = first_subscriber_id;
		this->second_subscriber_id = second_subscriber_id;
	}
	this->distance = distance;
}

std::string const& ProximityTrigger::get_id() const
{
	return id;
}

std::string const& ProximityTrigger::get_first_subscriber_id() const
{
	return first_subscriber_id;
}

std::string const& ProximityTrigger::get_second_subscriber_id() const
{
	return second_subscriber_id;
}

unsigned ProximityTrigger::get_distance() const
{
	return distance;
}

void ProximityTrigger::action() const
{
	std::string const msg("subscriber with id '" + first_subscriber_id + "' - subscriber with id '" + second_subscriber_id + ".");
	spdlog::info(msg);
}