//
// Created by ghitsh on 23.11.23.
//

#ifndef LOCATOR_AREA_H
#define LOCATOR_AREA_H


#include <string>
#include <utility>


class Area {
public:
	Area(unsigned, std::string, int, int, unsigned);

	// Copy constructor
	Area(Area const&);

	Area& operator=(Area const& other);

	unsigned get_id() const;

	std::string const& get_name() const; // should be non-empty string

	std::pair<int, int> const& get_location() const;

	unsigned get_radius() const;

	std::string const& set_name(std::string);

	std::pair<int, int> const& set_location(int, int);

	unsigned set_radius(unsigned);

private:
	unsigned id;
	std::string name;
	std::pair<int, int> location;
	unsigned radius; // Radius of an area
};


#endif //LOCATOR_AREA_H
