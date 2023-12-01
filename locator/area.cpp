#include "area.h"


Area::Area(unsigned id, std::string name, int x_coordinate, int y_coordinate, unsigned radius) :
		id(id),
		name(std::move(name)),
		location(x_coordinate, y_coordinate),
		radius(radius)
{}

Area::Area(Area const &other)
{
	id = other.get_id();
	name = other.get_name();
	location = other.get_location();
	radius = other.get_radius();
}

Area &Area::operator=(const Area &other)
{
	id = other.get_id();
	name = other.get_name();
	location = other.get_location();
	radius = other.get_radius();

	return *this;
}

unsigned Area::get_id() const
{
	return id;
}

std::string const &Area::get_name() const
{
	return name;
}

std::pair<int, int> const &Area::get_location() const
{
	return location;
}

unsigned Area::get_radius() const
{
	return radius;
}

std::string const &Area::set_name(std::string new_name)
{
	name = std::move(new_name);
	return name;
}

std::pair<int, int> const &Area::set_location(int new_x_coordianate, int new_y_coordinate)
{
	location = {new_x_coordianate, new_y_coordinate};
	return location;
}

unsigned Area::set_radius(unsigned new_radius)
{
	radius = new_radius;
	return radius;
}

int Area::get_x() const
{
	return location.first;
}

int Area::get_y() const
{
	return location.second;
}

int Area::set_x(int x)
{
	return location.first = x;
}

int Area::set_y(int y)
{
	return location.second = y;
}