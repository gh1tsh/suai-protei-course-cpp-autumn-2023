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
	locator.load_subscribers_data_from_file("/home/ghitsh/suai/suai-protei-course-cpp/data/subs_data.json");
	locator.dump_subscribers();
}
