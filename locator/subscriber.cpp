#include "subscriber.h"


Subscriber::Subscriber(std::string id,
                       int x_coordinate,
                       int y_coordinate) : id(std::move(id)), location(x_coordinate, y_coordinate)
{};

Subscriber::~Subscriber()
{
	for (auto const& t : triggers) delete t;
	while (!triggers.empty())
		triggers.pop_back();
}

std::string const& Subscriber::get_id() const
{
	return id;
}

std::pair<int, int> const& Subscriber::get_location() const
{
	return location;
}

int Subscriber::get_x() const
{
	return location.first;
}

int Subscriber::get_y() const
{
	return location.second;
}

int Subscriber::set_x(int x)
{
	return location.first = x;
}

int Subscriber::set_y(int y)
{
	return location.second = y;
}

std::string Subscriber::to_string() const
{
	std::string result = "Subscriber { id: \"";
	result += id;
	result += "\", location: [";
	result += std::to_string(location.first);
	result += ", ";
	result += std::to_string(location.second);
	result += "] }";
	return result;
}

ProximityTrigger* Subscriber::add_trigger(ProximityTrigger* t)
{
//	triggers.insert(std::pair<std::string, ProximityTrigger*>(t->get_second_subscriber_id(), t));
	triggers.push_back(t);
	return t;
}

bool Subscriber::has_trigger(std::string const& sid) const
{
	if (triggers.empty()) {
		return false;
	}
	std::list<ProximityTrigger*>::const_iterator t = triggers.end();
	for (auto iter = triggers.begin(); iter != triggers.end(); ++iter) {
		if ((*iter)->get_second_subscriber_id() == sid) {
			t = iter;
			break;
		}
	}
	if (t == triggers.end()) {
		return false;
	} else {
		return true;
	}
}

std::list<ProximityTrigger> Subscriber::get_triggers() const
{
	std::list<ProximityTrigger> list_triggers;
	for (auto const& trigger : triggers) {
		list_triggers.push_back(*trigger);
	}
	return list_triggers;
}
void Subscriber::remove_trigger(std::string const& trigger_id)
{
	std::list<ProximityTrigger*>::const_iterator target = triggers.end();
	for (auto iter = triggers.begin(); iter != triggers.end(); ++iter) {
		if ((*iter)->get_id() == trigger_id) {
			target = iter;
			break;
		}
	}
	if (target == triggers.end()) {
		spdlog::error("There is no trigger with id " + trigger_id);
	} else {
		delete *target;
		triggers.erase(target);
	}
}
