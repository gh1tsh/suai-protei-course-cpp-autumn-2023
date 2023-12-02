#ifndef LOCATOR_SUBSCRIBER_H
#define LOCATOR_SUBSCRIBER_H


#include "zone.h"

#include <string>
#include <utility>


class Subscriber
{
public:
	Subscriber(std::string, int, int);

	explicit Subscriber(Subscriber const*);

	Subscriber& operator=(Subscriber const*);

	std::string const& get_id() const;

	std::pair<int, int> const& get_location() const;

	std::pair<int, int> const& set_location(int, int);

	int get_x() const;

	int get_y() const;

	int set_x(int);

	int set_y(int);

private:
	std::string id;
	std::pair<int, int> location;
};


#endif //LOCATOR_SUBSCRIBER_H
