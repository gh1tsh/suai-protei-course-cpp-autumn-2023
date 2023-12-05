//
// Created by ghitsh on 04.12.23.
//

#include "proximity_trigger.h"

#include <utility>

ProximityTrigger::ProximityTrigger(std::string id, std::string first_subscriber_id, std::string second_subscriber_id,
								   unsigned distance) :
	id(std::move(id)),
	first_subscriber_id(std::move(first_subscriber_id)),
	second_subscriber_id(std::move(second_subscriber_id)),
	distance(distance)
{}

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
	std::string msg = "subscriber with id '" + first_subscriber_id + "' - subscriber with id '" + second_subscriber_id + ".";
	spdlog::info(msg);
}