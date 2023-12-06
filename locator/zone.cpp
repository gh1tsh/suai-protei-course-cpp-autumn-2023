#include "zone.h"

#include <spdlog/spdlog.h>


Zone::Zone(unsigned id, std::string name, int x_coordinate, int y_coordinate, unsigned radius) :
		id(id),
		name(std::move(name)),
		location(x_coordinate, y_coordinate),
		radius(radius)
		// 'triggers' map's constructor invokes implicitly
{}

Zone::~Zone()
{
	for (auto const& t : triggers) delete t;
	while (!triggers.empty())
		triggers.pop_back();
}

unsigned Zone::get_id() const
{
	return id;
}

std::string const& Zone::get_name() const
{
	return name;
}

std::pair<int, int> const& Zone::get_location() const
{
	return location;
}

unsigned Zone::get_radius() const
{
	return radius;
}

std::string const& Zone::set_name(std::string new_name)
{
	name = std::move(new_name);
	return name;
}

std::pair<int, int> const& Zone::set_location(int new_x_coordianate, int new_y_coordinate)
{
	location = {new_x_coordianate, new_y_coordinate};
	return location;
}

unsigned Zone::set_radius(unsigned new_radius)
{
	radius = new_radius;
	return radius;
}

int Zone::get_x() const
{
	return location.first;
}

int Zone::get_y() const
{
	return location.second;
}

int Zone::set_x(int x)
{
	return location.first = x;
}

int Zone::set_y(int y)
{
	return location.second = y;
}

ZoneTrigger* Zone::add_trigger(ZoneTrigger* t)
{
//	triggers.insert(std::pair<std::string, ZoneTrigger*>(t->get_subscriber_id(), t));
//	triggers[t->get_subscriber_id()] = t;
	triggers.push_back(t);
	return t;
}

void Zone::remove_trigger(std::string const& trigger_id)
{
	std::list<ZoneTrigger*>::iterator target = triggers.end();
	for (auto iter = triggers.begin(); iter != triggers.end(); ++iter) {
		if ((*iter)->get_id() == trigger_id) {
			target = iter;
			break;
		}
	}
//	auto target = triggers.find(trigger_id);
	if (target == triggers.end()) {
		// throw exception about lack of trigger with such id
		spdlog::error("No trigger with id " + trigger_id);
	} else {
		delete *target;
		triggers.erase(target);
	}
}

std::string Zone::to_string() const
{
	std::string result = "Zone { id: ";
	result += std::to_string(id);
	result += ", name: ";
	result += name;
	result += ", location: [";
	result += std::to_string(location.first);
	result += ", ";
	result += std::to_string(location.second);
	result += "], radius: ";
	result += std::to_string(radius);
	result += " }";
	return result;
}
bool Zone::has_trigger(std::string const& sid, Event event_type) const
{
	if (triggers.empty()) {
		return false;
	}
	std::list<ZoneTrigger*>::const_iterator target = triggers.end();
	for (auto iter = triggers.begin(); iter != triggers.end(); ++iter) {
		if ((*iter)->get_subscriber_id() == sid
		    && (*iter)->get_event_type() == event_type) {
			target = iter;
			break;
		}
	}
	if (target == triggers.end()) {
		return false;
	} else {
		return true;
	}
}

