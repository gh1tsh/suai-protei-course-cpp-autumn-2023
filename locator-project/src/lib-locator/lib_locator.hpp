//
// Created by ghitsh on 02.12.23.
//

#ifndef LOCATOR_LOCATOR_H
#define LOCATOR_LOCATOR_H


#include "../zone/zone.hpp"
#include "../subscriber/subscriber.hpp"
#include "../zone/zone_trigger.hpp"

#include <map>
#include <string>
#include <list>


class Locator
{
public:
	Locator();

	~Locator();

	Zone* add_zone(unsigned, std::string const&, int, int, unsigned);

	Zone const& get_zone(unsigned) const;

	Zone* get_zone_ptr(unsigned);

	Subscriber* add_subscriber(std::string const&, int, int);

	Subscriber const& get_subscriber(std::string const& id) const;

	Subscriber* get_subscriber_ptr(std::string const&);

	std::list<Subscriber> get_subscribers_in_zone(unsigned) const;

	std::list<Zone> get_subscriber_zones(std::string const&) const;

	void dump_subscribers() const;

	void dump_zones() const;

	void dump_zone_subscribers() const;

	void dump_subscriber_zones() const;

	void load_subscriber_data_from_file(std::string const& path_to_file);

	void load_locator_config();

	void add_zone_trigger(std::string const&, unsigned, std::string const&, Event);

	void add_proximity_trigger(std::string const&, std::string const&, std::string const&, unsigned);

	std::pair<int, int> const& set_subscriber_location(const std::string&, int, int);

	bool is_subscriber_in_zone(std::string const&, unsigned) const;

private:
	std::map<std::string, Subscriber*>			subscribers;
	std::map<unsigned, Zone*> 					zones;
	std::map<std::string, std::list<Zone*>> 	subscriber_zones;
	std::map<unsigned, std::list<Subscriber*>> 	zone_subscribers;

	void update_data();

	void add_subscriber_zone_relation(std::string const&, unsigned);

	void remove_subscriber_zone_relation(std::string const&, unsigned);

	bool check_subscriber_zone_relation_exist(std::string const&, unsigned) const;

	unsigned calculate_square_distance_between_subscribers(std::string const&, std::string const&) const;

	void subscriber_location_changed(std::string const&) const;

	bool check_subscriber_exist(std::string const&) const;

	bool check_zone_exist(unsigned) const;
};


#endif //LOCATOR_LOCATOR_H
