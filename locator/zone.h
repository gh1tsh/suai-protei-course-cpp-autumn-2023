#ifndef LOCATOR_ZONE_H
#define LOCATOR_ZONE_H


#include "zone_trigger.h"

#include <string>
#include <utility>
#include <map>
#include <list>


class Zone
{
public:
	Zone(unsigned, std::string, int, int, unsigned);

	~Zone();

	unsigned get_id() const;

	std::string const& get_name() const;

	std::pair<int, int> const& get_location() const;

	unsigned get_radius() const;

	std::string const& set_name(std::string);

	std::pair<int, int> const& set_location(int, int);

	unsigned set_radius(unsigned);

	int get_x() const;

	int get_y() const;

	int set_x(int);

	int set_y(int);

	std::string to_string() const;

	ZoneTrigger* add_trigger(ZoneTrigger*);

	void remove_trigger(std::string const&);

	ZoneTrigger const& get_trigger(std::string const&) const;

	bool has_trigger(std::string const&, Event) const;

private:
	unsigned id;
	std::string name;
	std::pair<int, int> location;
	unsigned radius;
	/*
	 * The 'triggers' hash table stores all triggers that subscribers have on certain zone
	 * std::string - subscriber id
	 * ZoneTrigger* - pointer to trigger
	 */
//	std::map<std::string, ZoneTrigger*> triggers;
	std::list<ZoneTrigger*> triggers;
};


#endif //LOCATOR_ZONE_H
