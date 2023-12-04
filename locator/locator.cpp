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

Zone* Locator::add_zone(unsigned id, std::string const& name, int x_coordinate, int y_coordinate, unsigned radius)
{
	auto new_zone = new Zone(id, name, x_coordinate, y_coordinate, radius);
	zones.insert(std::pair<unsigned, Zone*>(id, new_zone));
	return new_zone;
}

Subscriber* Locator::add_subscriber(std::string const& id, int x_coordinate, int y_coordinate)
{
	auto new_subscriber = new Subscriber(id, x_coordinate, y_coordinate);
	subscribers.insert(std::pair<std::string, Subscriber*>(id, new_subscriber));
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

void Locator::load_subscribers_data_from_file(std::string path_to_file)
{
	std::ifstream subscribers_data_json_file(path_to_file);
	// TODO: add error handling logic here
	json subscribers_data = json::parse(subscribers_data_json_file);
	for (auto const& sub : subscribers_data["subscribers"]) {
		auto* new_subscriber = new Subscriber(sub["id"], sub["location"]["x"], sub["location"]["y"]);
		subscribers.insert(std::pair<std::string, Subscriber*>(new_subscriber->get_id(), new_subscriber));
	}
	/*
	 * EXAMPLE
	 *
	 *
	 * // Access subscribers array and iterate through its elements
    if (data.contains("subscribers")) {
        for (const auto& subscriber : data["subscribers"]) {
            std::string id = subscriber["id"];
            int x = subscriber["location"]["x"];
            int y = subscriber["location"]["y"];

            std::cout << "Subscriber ID: " << id << std::endl;
            std::cout << "Location - X: " << x << ", Y: " << y << std::endl;
            std::cout << std::endl;
        }
    } else {
        std::cerr << "No subscribers found in JSON." << std::endl;
        return 1;
    }
	 *
	 */
}