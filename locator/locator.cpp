//
// Created by ghitsh on 02.12.23.
//

#include "locator.h"
#include "zone.h"

#include <utility>
#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;


Locator::Locator()
{}

Locator::~Locator()
{
 // 1. delete all instances in zone_subscribers and subscriber_zones
 // 2. finally delete memory for instances via subscribers and zones maps
}

Zone* Locator::add_zone(unsigned id, std::string const& name, int x_coordinate, int y_coordinate, unsigned radius)
{
	auto new_zone = new Zone(id, name, x_coordinate, y_coordinate, radius);
	zones.insert(std::pair<unsigned, Zone*>(id, new_zone));
	update_data();
	return new_zone;
}

Subscriber* Locator::add_subscriber(std::string const& id, int x_coordinate, int y_coordinate)
{
	auto new_subscriber = new Subscriber(id, x_coordinate, y_coordinate);
	subscribers.insert(std::pair<std::string, Subscriber*>(id, new_subscriber));
	update_data();
	return new_subscriber;
}

Zone const& Locator::get_zone(unsigned id) const
{
	return *zones.at(id);
}

Subscriber const& Locator::get_subcriber(std::string const& id) const
{
	return *subscribers.at(id);
}

void Locator::dump_subscribers() const
{
	std::cout << "Registered subscribers:" << std::endl;
	for (auto const& [key, value] : subscribers) {
		std::cout << '\t' << value->to_string() << std::endl;
	}
}

void Locator::dump_zones() const
{
	std::cout << "Registered zones:" << std::endl;
	for (auto const& [key, value] : zones) {
		std::cout << '\t' << value->to_string() << std::endl;
	}
}

void Locator::dump_zone_subscribers() const
{
	std::cout << "List of zones and related subscribers:" << std::endl;
	for (auto const& [zid, l] : zone_subscribers) {
		std::cout << "\tZone id: " << zid << std::endl;
		std::cout << "\tTotal amount of subscribers: " << l.size() << std::endl;
		std::cout << "\tSubscribers:" << std::endl;
		for (auto const& e : l)
			std::cout << "\t\t" << e->to_string() << std::endl;
		std::cout << std::endl;
	}
}

void Locator::dump_subscriber_zones() const
{
	std::cout << "List of subscribers and related zones:" << std::endl;
	for (auto const& [sid, l] : subscriber_zones) {
		std::cout << "\tSubscriber id: " << sid << std::endl;
		std::cout << "\t Total amount of zones: " << l.size() << std::endl;
		std::cout << "\tZones:" << std::endl;
		for (auto const& e : l)
			std::cout << "\t\t" << e->to_string() << std::endl;
		std::cout << std::endl;
	}
}

bool Locator::is_subscriber_in_zone(std::string subscriber_id, unsigned zone_id) const
{
	std::pair<int, int> subscriber_location = subscribers.at(subscriber_id)->get_location();
	std::pair<int, int> zone_location = zones.at(zone_id)->get_location();
	unsigned zone_radius = zones.at(zone_id)->get_radius();
	bool result = ( ((subscriber_location.first - zone_location.first) * (subscriber_location.first - zone_location.first)) + ((subscriber_location.second - zone_location.second) * (subscriber_location.second - zone_location.second)) ) <= zone_radius * zone_radius;
	return result;
}

void Locator::add_subscriber_zone_relation(std::string const& sid, unsigned zid)
{
	subscriber_zones[sid].push_back(zones.at(zid));
	zone_subscribers[zid].push_back(subscribers.at(sid));
}

void Locator::remove_subscriber_zone_relation(std::string const& sid, unsigned int zid)
{
	std::list<Zone*>& zones_list = subscriber_zones.at(sid); // list of zones related to subscriber with id "sid"
	auto iter_to_target_zone = std::find(zones_list.begin(), zones_list.end(), zones.at(zid));
	zones_list.erase(iter_to_target_zone);

	std::list<Subscriber*>& subscribers_list = zone_subscribers.at(zid);
	auto iter_to_target_subscriber = std::find(subscribers_list.begin(), subscribers_list.end(), subscribers.at(sid));
	subscribers_list.erase(iter_to_target_subscriber);
}

bool Locator::check_existence_subscriber_zone_relation(std::string const& sid, unsigned zid) const
{
	auto it = subscriber_zones.find(sid);
	if (it == subscriber_zones.end()) {
		// if there is no such a key in the map
		return false;
	} else if (it->second.empty()) {
		// if list of zones is empty
		return false;
	} else if (std::find(it->second.begin(), it->second.end(), zones.at(zid)) == it->second.end()) {
		// if there is no such a zone in the list
		return false;
	} else {
		return true;
	}
}

void Locator::update_data()
{
	for (auto const& [sid, sub] : subscribers) {
		// 'sid' and 'zid' stand for 'subscriber id' and 'zone id' respectively
		for (auto const& [zid, zone] : zones) {
			// cs and cz stand for 'current subscriber' and 'current zone'
			if (is_subscriber_in_zone(sid, zid)
			    && check_existence_subscriber_zone_relation(sid, zid)) {
				continue;
			} else if (is_subscriber_in_zone(sid, zid)
				   && !check_existence_subscriber_zone_relation(sid, zid)) {
				add_subscriber_zone_relation(sid, zid);
			} else if (!is_subscriber_in_zone(sid, zid)
				   && check_existence_subscriber_zone_relation(sid, zid)) {
				remove_subscriber_zone_relation(sid, zid);
			} else {
				continue;
			}
		}
	}
}

void Locator::load_subscribers_data_from_file(std::string path_to_file)
{
	std::ifstream subscribers_data_json_file(path_to_file);
	// TODO: add error handling logic
	// TODO: add json file validation according to schema
	json subscribers_data = json::parse(subscribers_data_json_file);
	for (auto const& sub : subscribers_data["subscribers"]) {
		add_subscriber(sub["id"], sub["location"]["x"], sub["location"]["y"]);
//		auto* new_subscriber = new Subscriber(sub["id"], sub["location"]["x"], sub["location"]["y"]);
//		subscribers.insert(std::pair<std::string, Subscriber*>(new_subscriber->get_id(), new_subscriber));
	}
}

void Locator::load_locator_config()
{
	// TODO: add json file validation according to schema
	std::ifstream locator_config_json_file("../config/locator_config.json");
	json locator_config_data = json::parse(locator_config_json_file);
	// TODO: implement processing redis config and gRPC config in the future
	for (auto const& cz : locator_config_data["zones"]) {
		add_zone(cz["id"], cz["name"], cz["x"], cz["y"], cz["radius"]);
//		auto* new_zone = new Zone(cz["id"], cz["name"], cz["x"], cz["y"], cz["radius"]);
//		zones.insert(std::pair<unsigned, Zone*>(new_zone->get_id(), new_zone));
	}
}

void Locator::add_zone_trigger(
	std::string const& trigger_id,
	std::string const& subscriber_id,
	unsigned int zone_id,
	Event event_type)
{
	auto* new_trigger = new ZoneTrigger(trigger_id, subscriber_id, zone_id, event_type);
	zones.at(zone_id)->add_trigger(new_trigger);
}

std::pair<int, int> const& Locator::set_subscriber_location(std::string subscriber_id, int new_x_coordinate,
															int new_y_coordinate)
{
	subscribers.at(subscriber_id)->set_x(new_x_coordinate);
	subscribers.at(subscriber_id)->set_y(new_y_coordinate);
	// TODO
}
