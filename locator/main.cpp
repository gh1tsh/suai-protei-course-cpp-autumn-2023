#include <iostream>

#include "locator.h"
#include "subscriber.h"
#include "zone.h"

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>


using json = nlohmann::json;


int main()
{
	Locator locator;
	locator.load_locator_config();
	locator.add_zone_trigger("zone_0_trigger", 0, "+71111111111", Event::ENTERING_EXITING_ZONE);
	locator.load_subscriber_data_from_file("../data/data-examples/subscriber_data_example.json");
	locator.add_proximity_trigger("test", "+73333333333", "+74444444444", 5);
	locator.set_subscriber_location("+73333333333", -2, -2);
	locator.set_subscriber_location("+73333333333", 3, 3);
}
