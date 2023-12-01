//
// Created by ghitsh on 25.11.23.
//

#ifndef LOCATOR_SUBSCRIBER_H
#define LOCATOR_SUBSCRIBER_H


#include <string>
#include <utility>


class Subscriber {
public:
	Subscriber(std::string, int, int);

	explicit Subscriber(Subscriber const*);

	Subscriber& operator=(Subscriber const*);

	std::string const& get_id() const;

	std::pair<int, int> const& get_location() const;

	std::pair<int, int> const& set_location(int, int);

private:
	std::string id;
	std::pair<int, int> location;
};


#endif //LOCATOR_SUBSCRIBER_H
