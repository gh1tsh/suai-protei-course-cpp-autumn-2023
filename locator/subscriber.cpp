#include "subscriber.h"


Subscriber::Subscriber(std::string id,
                       int x_coordinate,
                       int y_coordinate) : id(std::move(id)), location(x_coordinate, y_coordinate)
{};

std::string const& Subscriber::get_id() const
{
	return id;
}

std::pair<int, int> const& Subscriber::get_location() const
{
	return location;
}

int Subscriber::get_x() const
{
	return location.first;
}

int Subscriber::get_y() const
{
	return location.second;
}

int Subscriber::set_x(int x)
{
	return location.first = x;
}

int Subscriber::set_y(int y)
{
	return location.second = y;
}

std::string Subscriber::to_string() const
{
	std::string result = "Subscriber { id: \"";
	result += id;
	result += "\", location: [";
	result += std::to_string(location.first);
	result += ", ";
	result += std::to_string(location.second);
	result += "] }";
	return result;
}
