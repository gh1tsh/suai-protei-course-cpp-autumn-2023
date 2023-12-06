//
// Created by ghitsh on 02.12.23.
//

#include "locator.h"

#include <utility>
#include <fstream>
#include <iostream>
#include <cmath>
#include <exception>

#include <nlohmann/json.hpp>

using json = nlohmann::json;


Locator::Locator()
{}

Locator::~Locator()
{
	while (!subscriber_zones.empty())
		subscriber_zones.erase(subscriber_zones.begin());
	while (!zone_subscribers.empty())
		zone_subscribers.erase(zone_subscribers.begin());
	for (auto& e : zones) delete e.second;
	for (auto& e : subscribers) delete e.second;
	while (!zones.empty())
		zones.erase(zones.begin());
	while (!subscribers.empty())
		subscribers.erase(subscribers.begin());
}

Zone* Locator::add_zone(unsigned id,
			std::string const& name,
			int x_coordinate,
			int y_coordinate,
			unsigned radius)
{
	try {
		auto new_zone = new Zone(
			id,
			name,
			x_coordinate,
			y_coordinate,
			radius
		);
		zones[id] = new_zone;
		update_data();
		return new_zone;
	} catch (std::exception& e) {
		spdlog::error(
		    "Error adding new zone.\nDescription:\n\t{}",
		    e.what());
		return nullptr;
	}
}

Subscriber* Locator::add_subscriber(std::string const& id,
				    int x_coordinate,
				    int y_coordinate)
{
	try {
		auto new_subscriber = new Subscriber(id, x_coordinate, y_coordinate);
		subscribers[id] = new_subscriber;
		update_data();
		return new_subscriber;
	} catch (std::exception& e) {
		spdlog::error(
		    "Error adding new subscriber.\nDescription:\n\t{}",
		    e.what());
		return nullptr;
	}

}

Zone const& Locator::get_zone(unsigned id) const
{
	return *zones.at(id);
}

Subscriber const& Locator::get_subscriber(std::string const& id) const
{
	return *subscribers.at(id);
}

std::list<Subscriber> Locator::get_subscribers_in_zone(unsigned zid) const
{
	std::list<Subscriber> list_subscribers_in_zone;
	for (auto const& e : zone_subscribers.at(zid)) {
		list_subscribers_in_zone.push_back(*e);
	}
	return list_subscribers_in_zone;
}

std::list<Zone> Locator::get_subscriber_zones(std::string const& sid) const
{
	std::list<Zone> list_subscriber_zones;
	for (auto const& e : subscriber_zones.at(sid)) {
		list_subscriber_zones.push_back(*e);
	}
	return list_subscriber_zones;
}

void Locator::dump_subscribers() const
{
	std::cout << "Registered subscribers:" << std::endl;
	if (zones.empty()) {
		std::cout << "\tEMPTY" << std::endl;
	} else {
		for (auto const& [key, value] : subscribers) {
			std::cout << '\t' << value->to_string() << std::endl;
		}
	}
}

void Locator::dump_zones() const
{
	std::cout << "Registered zones:" << std::endl;
	if (zones.empty()) {
		std::cout << "\tEMPTY" << std::endl;
		std::cout << std::endl;
	} else {
		for (auto const& [key, value] : zones) {
			std::cout << '\t' << value->to_string() << std::endl;
		}
		std::cout << std::endl;
	}
}

void Locator::dump_zone_subscribers() const
{
	std::cout << "List of zones and related subscribers:" << std::endl;
	if (zone_subscribers.empty()) {
		std::cout << "\tEMPTY" << std::endl;
	} else {
		for (auto const& [zid, l] : zone_subscribers) {
			std::cout << "\tZone id: " << zid << std::endl;
			std::cout << "\tTotal amount of subscribers: " << l.size() << std::endl;
			std::cout << "\tSubscribers:" << std::endl;
			for (auto const& e : l)
				std::cout << "\t\t" << e->to_string() << std::endl;
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void Locator::dump_subscriber_zones() const
{
	std::cout << "List of subscribers and related zones:" << std::endl;
	if (subscriber_zones.empty()) {
		std::cout << "\tEMPTY" << std::endl;
	} else {
		for (auto const& [sid, l] : subscriber_zones) {
			std::cout << "\tSubscriber id: " << sid << std::endl;
			std::cout << "\t Total amount of zones: " << l.size() << std::endl;
			std::cout << "\tZones:" << std::endl;
			for (auto const& e : l)
				std::cout << "\t\t" << e->to_string() << std::endl;
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

bool Locator::is_subscriber_in_zone(std::string const& subscriber_id,
				    unsigned zone_id) const
{
	if (subscribers.find(subscriber_id) == subscribers.end()) {
		throw std::invalid_argument("The subscriber with id '"
					    + subscriber_id
					    + "' does not exist.");
	}
	if (zones.find(zone_id) == zones.end()) {
		throw std::invalid_argument("The zone with id '"
					    + std::to_string(zone_id)
					    + "' does not exist.");
	}
	std::pair<int, int> subscriber_location = subscribers.at(subscriber_id)->get_location();
	std::pair<int, int> zone_location = zones.at(zone_id)->get_location();
	unsigned zone_radius = zones.at(zone_id)->get_radius();

	/*
	 * The equation below allows you to determine whether a point
	 * with coordinates [x; y] is in a circle centered at [xc; yc]
	 * of radius r. In general, it looks like this:
	 *                      (x - xc)^2 + (y-yc)^2 = r^2.
	 *
	 * Let's introduce the notation. I'll call the part (x - xc)^2 'x_part';
	 * part (y - yc)^2 'y_part'. And finally part r^2 'r_part'.
	 *
	 * This renaming is done in order to split a long equation into
	 * several simpler parts, thus making it less long and more readable
	 * in the code.
	 */
	int x_part = ((subscriber_location.first - zone_location.first) * (subscriber_location.first - zone_location.first));
	int y_part = ((subscriber_location.second - zone_location.second) * (subscriber_location.second - zone_location.second));
	int r_part = (int)(zone_radius * zone_radius);
	bool result = x_part + y_part <= r_part;

	return result;
}

void Locator::add_subscriber_zone_relation(std::string const& sid, unsigned zid)
{
	subscriber_zones[sid].push_back(zones.at(zid));
	zone_subscribers[zid].push_back(subscribers.at(sid));
}

void Locator::remove_subscriber_zone_relation(std::string const& sid,
					      unsigned int zid)
{
	// list of zones related to subscriber with id "sid"
	std::list<Zone*>& zones_list = subscriber_zones.at(sid);
	auto iter_to_target_zone = std::find(zones_list.begin(), zones_list.end(), zones.at(zid));
	zones_list.erase(iter_to_target_zone);

	std::list<Subscriber*>& subscribers_list = zone_subscribers.at(zid);
	auto iter_to_target_subscriber = std::find(subscribers_list.begin(), subscribers_list.end(), subscribers.at(sid));
	subscribers_list.erase(iter_to_target_subscriber);
}

bool Locator::check_subscriber_zone_relation_exist(
	std::string const& subscriber_id,
	unsigned zone_id) const
{
	if (subscribers.find(subscriber_id) == subscribers.end()) {
		throw std::invalid_argument("The subscriber with id '"
		                                + subscriber_id
		                                + "' does not exist.");
	}
	if (zones.find(zone_id) == zones.end()) {
		throw std::invalid_argument("The zone with id '"
		                                + std::to_string(zone_id)
		                                + "' does not exist.");
	}
	auto it = subscriber_zones.find(subscriber_id);
	// NOTE: you can refactor this part of the code to a single "if...else" block
	if (it == subscriber_zones.end()) {
		// if there is no such a key in the map
		return false;
	} else if (it->second.empty()) {
		// if the list of zones is empty
		return false;
	} else if (std::find(it->second.begin(), it->second.end(), zones.at(zone_id)) == it->second.end()) {
		// if there is no such a zone in the list
		return false;
	} else {
		return true;
	}
}

void Locator::update_data()
{
	// TODO: add function description
	for (auto const& [sid, sub] : subscribers) {
		// 'sid' and 'zid' stand for 'subscriber id' and 'zone id' respectively
		for (auto const& [zid, zone] : zones) {
			// cs and cz stand for 'current subscriber' and 'current zone'
			if (is_subscriber_in_zone(sid, zid)
			    && check_subscriber_zone_relation_exist(sid, zid)) {
				continue;
			} else if (is_subscriber_in_zone(sid, zid)
				   && !check_subscriber_zone_relation_exist(sid, zid)) {
				if (zones.at(zid)->has_trigger(sid, Event::ENTERING_ZONE)
				    || zones.at(zid)->has_trigger(sid, Event::ENTERING_EXITING_ZONE)) {
					zones.at(zid)->get_trigger_by_subscriber_id(sid).action();
				}
				add_subscriber_zone_relation(sid, zid);
			} else if (!is_subscriber_in_zone(sid, zid)
				   && check_subscriber_zone_relation_exist(sid, zid)) {
				if (zones.at(zid)->has_trigger(sid, Event::EXITING_ZONE)
				    || zones.at(zid)->has_trigger(sid, Event::ENTERING_EXITING_ZONE)) {
					zones.at(zid)->get_trigger_by_subscriber_id(sid).action();
				}
				remove_subscriber_zone_relation(sid, zid);
			} else {
				continue;
			}
		}
	}
}

void Locator::load_subscriber_data_from_file(std::string const& path_to_file)
{
	std::ifstream subscribers_data_json_file;
	try {
		subscribers_data_json_file.open(path_to_file);
	} catch (std::exception& e) {
		spdlog::error(
			"Error reading subscriber data from file '{}'.\n"
			"Description:\n\t{}\nOutcome: subscriber data will not "
			"be load from the file.",
			path_to_file,
			e.what());
		return;
	}
	// TODO: add json file validation according to schema
	json subscribers_data;
	try {
		subscribers_data = json::parse(subscribers_data_json_file);
	} catch (json::parse_error& e) {
		spdlog::error("Error parsing json file '{}'.\n"
			      "Description:\n\t{}\nOutcome: subscriber data "
			      "will not be load from the file.",
			      path_to_file,
			      e.what());
		return;
	}
	for (auto const& sub : subscribers_data["subscribers"]) {
		try {
			add_subscriber(
			    sub["id"],
			    sub["location"]["x"],
			    sub["location"]["y"]
			);
		} catch (std::exception& e) {
			spdlog::error("Error adding subscriber with id "
				      "'{}'.\nDescription:\n\t{}\nOutcome: "
				      "subscriber will not be load.",
				      sub["id"],
				      e.what());
		}
	}
}

void Locator::load_locator_config()
{
	// TODO: add json file validation according to schema
	std::ifstream locator_config_json_file;
	try {
		locator_config_json_file.open("../config/locator_config.json");
	} catch (std::exception& e) {
		spdlog::error(
		    "Error reading locator configuration from file "
		    "'../config/locator_config.json'.\nDescription:\n\t{}\n"
		    "Outcome: locator configuration will not be load from the "
		    "file. Program shutdown...",
		    e.what());
		exit(0);
	}
	json locator_config_data;
	try {
		locator_config_data = json::parse(locator_config_json_file);
	} catch (json::parse_error& e) {
		spdlog::error("Error parsing json file "
			      "'../config/locator_config.json'.\n"
			      "Description:\n\t{}\nOutcome: locator "
			      "configuration will not be load from the "
		              "file. Program shutdown...",
		              e.what());
		exit(0);
	}
	for (auto const& cz : locator_config_data["zones"]) {
		try {
			add_zone(
			    cz["id"],
			    cz["name"],
			    cz["x"],
			    cz["y"],
			    cz["radius"]
			);
		} catch (std::exception& e) {
			spdlog::error("Error adding zone with id "
			              "'{}' and name '{}'.\n"
				      "Description:\n\t{}\nOutcome: "
			              "zone will not be load.",
			              cz["id"],
				      cz["name"],
			              e.what());
		}
	}
	// TODO: implement processing redis config and gRPC config
}

void Locator::add_zone_trigger(
	std::string const& trigger_id,
	unsigned int zone_id,
	std::string const& subscriber_id,
	Event event_type)
{
	if (!check_zone_exist(zone_id)) {
		throw std::invalid_argument("Cannot add ZoneTrigger with"
		                            "identifier '" + trigger_id + "."
		                                                          "Zone with id "
		                                + std::to_string(zone_id)
		                                + " does not exist.");
	}
	if (zones.at(zone_id)->check_trigger_exist(trigger_id)) {
		spdlog::info("ZoneTrigger with identifier '{}' already"
			     "exists.", trigger_id);
		return;
	}
	try {
		auto* new_trigger = new ZoneTrigger(
		    trigger_id,
		    subscriber_id,
		    zone_id,
		    event_type
		);
		zones.at(zone_id)->add_trigger(new_trigger);
	} catch (std::exception& e) {
		spdlog::error("Error adding new ZoneTrigger"
			      "with identifier {}.\nDescription:\n\t{}",
			      trigger_id,
			      e.what());
	}
}

void Locator::add_proximity_trigger(
    // TODO: нельзя добавить проксимити триггер, если одного из абонентов ещё не существует
    std::string const& trigger_id,
    std::string const& first_subscriber_id,
    std::string const& second_subscriber_id,
    unsigned distance)
{
	if (!check_subscriber_exist(first_subscriber_id)) {
		throw std::invalid_argument("Error adding trigger '"
					    + trigger_id + "'. Subscriber "
					    "with identifier '"
					    + first_subscriber_id
					    + "' does not exist.");
	}
	if (!check_subscriber_exist(second_subscriber_id)) {
		throw std::invalid_argument("Error adding trigger '"
		                                + trigger_id + "'. Subscriber "
		                                               "with identifier '"
		                                + second_subscriber_id
		                                + "' does not exist.");
	}
	if (subscribers.at(first_subscriber_id)->check_trigger_exist(trigger_id)) {
		spdlog::info("ProximityTrigger with identifier '{}' already"
		             "exists.", trigger_id);
		return;
	}
	auto* new_trigger = new ProximityTrigger(
	    trigger_id,
	    first_subscriber_id,
	    second_subscriber_id,
	    distance
	);
	try {
		subscribers.at(first_subscriber_id)->add_trigger(new_trigger);
		subscriber_location_changed(first_subscriber_id);
	} catch (std::exception& e) {
		spdlog::error("Error adding new ProximityTrigger"
		              "with identifier {}.\nDescription:\n\t{}",
		              trigger_id,
		              e.what());
	}
	try {
		auto* new_trigger_1 = new ProximityTrigger(
		    trigger_id,
		    first_subscriber_id,
		    second_subscriber_id,
		    distance
		);
		auto* new_trigger_2 = new ProximityTrigger(
		    trigger_id,
		    second_subscriber_id,
		    first_subscriber_id,
		    distance
		);
		subscribers.at(first_subscriber_id)->add_trigger(new_trigger_1);
		subscribers.at(second_subscriber_id)->add_trigger(new_trigger_2);
	} catch (std::exception& e) {
		spdlog::error("Error adding new ProximityTrigger"
		              "with identifier {}.\nDescription:\n\t{}",
		              trigger_id,
		              e.what());
	}
}

std::pair<int, int> const&
    Locator::set_subscriber_location(std::string const& subscriber_id,
				     int new_x_coordinate,
				     int new_y_coordinate)
{
	subscribers.at(subscriber_id)->set_x(new_x_coordinate);
	subscribers.at(subscriber_id)->set_y(new_y_coordinate);
	update_data();
	this->subscriber_location_changed(subscriber_id);
	return subscribers.at(subscriber_id)->get_location();
}

unsigned Locator::calculate_square_distance_between_subscribers(
    std::string const& first,
    std::string const& second) const
{
	std::pair<int, int> const& first_subscriber_location = subscribers.at(first)->get_location();
	std::pair<int, int> const& second_subscriber_location = subscribers.at(second)->get_location();
	int x1 = first_subscriber_location.first;
	int y1 = first_subscriber_location.second;
	int x2 = second_subscriber_location.first;
	int y2 = second_subscriber_location.second;
	return (unsigned)((abs(x1 - x2) * abs(x1 - x2))
				+ (abs(y1 - y2) * abs(y1 - y2)));
}

void Locator::subscriber_location_changed(std::string const& sid) const
{
	std::list<ProximityTrigger> subscriber_triggers = subscribers.at(sid)->get_triggers();
	for (auto const& t : subscriber_triggers) {
		unsigned current_distance = calculate_square_distance_between_subscribers(sid, t.get_second_subscriber_id());

		if (current_distance == (t.get_distance() * t.get_distance())) {
			t.action();
		}
	}
}
bool Locator::check_zone_exist(unsigned zone_id) const
{
	bool result = false;
	if (zones.find(zone_id) == zones.end()) {
		result = false;
	} else {
		result = true;
	}
	return result;
}
bool Locator::check_subscriber_exist(std::string const& subscriber_id) const
{
	bool result = false;
	if (subscribers.find(subscriber_id) == subscribers.end()) {
		result = false;
	} else {
		result = true;
	}
	return result;
}


/*
 * CUSTOM EXCEPTION EXAMPLE
 *
 * class DivideByZeroException : public std::runtime_error {
public:
    DivideByZeroException() : std::runtime_error("Divide by zero error") {}
};
 */