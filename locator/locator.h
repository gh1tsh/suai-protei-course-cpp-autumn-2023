//
// Created by ghitsh on 02.12.23.
//

#ifndef LOCATOR_LOCATOR_H
#define LOCATOR_LOCATOR_H


#include "zone.h"
#include "subscriber.h"

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


class Locator
{
public:
	Locator();

	~Locator();

	Zone* add_zone(unsigned, std::string const&, int, int, unsigned);

	Subscriber* add_subscriber(std::string const&, int, int);

	Zone const& get_zone(unsigned) const;

	Subscriber const& get_subcriber(const std::string&) const;

	void dump_subscribers() const;

	void dump_zones() const;

	void load_subscribers_data_from_file(std::string);

	void load_locator_config();

private:
	std::map<std::string, Subscriber*> subscribers;
	std::map<unsigned, Zone*> zones;
	std::map<std::string, std::list<Zone*>> zone_subscribers;
	std::map<unsigned, std::list<Subscriber*>> subscriber_zones;
};


#endif //LOCATOR_LOCATOR_H
