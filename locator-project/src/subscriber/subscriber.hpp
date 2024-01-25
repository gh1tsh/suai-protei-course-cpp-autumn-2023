#ifndef LOCATOR_SUBSCRIBER_H
#define LOCATOR_SUBSCRIBER_H


#include "../zone/zone.hpp"
#include "proximity_trigger.hpp"

#include <string>
#include <utility>
#include <list>


class Subscriber
{
public:
	Subscriber(const std::string&, int, int);

	~Subscriber();

	std::string const& get_id() const;

	std::pair<int, int> const& get_location() const;

	std::pair<int, int> const& set_location(int, int);

	int get_x() const;

	int get_y() const;

	int set_x(int);

	int set_y(int);

	std::string to_string() const;

	ProximityTrigger* add_trigger(ProximityTrigger*);

	void remove_trigger(std::string const&);

	ProximityTrigger const& get_trigger(std::string const&);

	bool has_trigger(std::string const&) const;

	std::list<ProximityTrigger> get_triggers() const;

	bool check_trigger_exist(std::string const&);

private:
	std::string id;
	std::pair<int, int> location;
	/*
	 * The 'triggers' hash table stores all triggers that subscriber has
	 * std::string - related subscriber id
	 * ProximityTrigger* - pointer to trigger
	 */
//	std::map<std::string, ProximityTrigger*> triggers;
	std::list<ProximityTrigger*> triggers;

	std::list<ProximityTrigger*>::iterator get_trigger_iter(std::string const&);
};



#endif //LOCATOR_SUBSCRIBER_H
