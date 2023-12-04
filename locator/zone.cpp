#include "zone.h"


Zone::Zone(unsigned id, std::string name, int x_coordinate, int y_coordinate, unsigned radius) :
		id(id),
		name(std::move(name)),
		location(x_coordinate, y_coordinate),
		radius(radius)
		// 'triggers' map's constructor invokes implicitly
{}

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
	triggers.insert(std::pair<std::string, ZoneTrigger*>(t->get_subscriber_id(), t));
	return t;
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
