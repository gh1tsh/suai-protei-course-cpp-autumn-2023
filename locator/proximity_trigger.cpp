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
