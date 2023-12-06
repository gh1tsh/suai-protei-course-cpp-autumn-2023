//
// Created by ghitsh on 02.12.23.
//

#ifndef LOCATOR_LOCATOR_H
#define LOCATOR_LOCATOR_H


#include "zone.h"
#include "subscriber.h"
#include "zone_trigger.h"

#include <map>
#include <string>
#include <list>

/*
 * JSON SCHEMA VALIDATION EXAMPLE
 *
 *
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    // Load JSON schema
    std::ifstream schemaFile("schema.json");
    json schema;
    schemaFile >> schema;

    // Your JSON data for validation
    json data = R"(
        {
            "name": "John Doe",
            "age": 30
        }
    )"_json;

    // Validate JSON data against the schema
    try {
        data.validate(schema);
        std::cout << "Validation successful!" << std::endl;
    } catch (const json::exception& e) {
        std::cout << "Validation failed: " << e.what() << std::endl;
    }

    return 0;
}

 */

/*
 * TODO:
 *      1) Реализовать деструкторы всех классов и проверить утечки памяти;
 *      2) Реализовать всю базовую логику обработки ошибок;
 */

class Locator
{
public:
	Locator();

	~Locator();

	Zone* add_zone(unsigned, std::string const&, int, int, unsigned);

	Zone const& get_zone(unsigned) const;

	Subscriber* add_subscriber(std::string const&, int, int);

	Subscriber const& get_subscriber(std::string const& id) const;

	std::list<Subscriber*> const& get_subscribers_in_zone(unsigned) const;

	std::list<Zone*> const& get_subscriber_zones(std::string const&) const;

	void dump_subscribers() const;

	void dump_zones() const;

	void dump_zone_subscribers() const;

	void dump_subscriber_zones() const;

	void load_subscribers_data_from_file(std::string const&);

	void load_locator_config();

	void add_zone_trigger(std::string const&, unsigned, std::string const&, Event);

	void add_proximity_trigger(std::string const&, std::string const&, std::string const&, unsigned);

	std::pair<int, int> const& set_subscriber_location(std::string, int, int);

	bool is_subscriber_in_zone(std::string, unsigned) const;

private:
	std::map<std::string, Subscriber*> subscribers;
	std::map<unsigned, Zone*> zones;
	std::map<std::string, std::list<Zone*>> subscriber_zones;
	std::map<unsigned, std::list<Subscriber*>> zone_subscribers;

	void update_data();

	void add_subscriber_zone_relation(std::string const&, unsigned);

	void remove_subscriber_zone_relation(std::string const&, unsigned);

	bool check_existence_subscriber_zone_relation(std::string const&, unsigned) const;

	unsigned calculate_square_distance_between_subscribers(std::string const&, std::string const&) const;

	void subscriber_location_changed(std::string const&) const;
};


#endif //LOCATOR_LOCATOR_H
