#include <iostream>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>


using json = nlohmann::json;


int main() {
	std::cout << "Hello, World!" << std::endl; // compiler check
	spdlog::info("Welcome to spdlog."); // sbdlog library check
	json data = json::parse(R"({ "text": "Hello, nlohman/json." })");
	std::cout << data["text"] << std::endl;
}
