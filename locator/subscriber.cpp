#include "subscriber.h"

#include <exception>


Subscriber::Subscriber(std::string const& id,
                       int x_coordinate,
                       int y_coordinate) : location(x_coordinate, y_coordinate)
{
	if (id.empty()) {
		throw std::invalid_argument("Subscriber identifier cannot be empty string.");
	} else {
		this->id = id;
	}
};

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

ProximityTrigger const&
	Subscriber::get_trigger(const std::string& trigger_id)
{
	auto target = get_trigger_iter(trigger_id);
	return *(*target);
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
	if (!check_trigger_exist(trigger_id)) {
		throw std::invalid_argument(this->to_string()
					    + "' does not have a trigger with id '" + trigger_id + "'.");
	} else {
		auto target = get_trigger_iter(trigger_id);
		delete *target;
		triggers.erase(target);
	}
}
bool Subscriber::check_trigger_exist(std::string const& trigger_id)
{
	auto target = get_trigger_iter(trigger_id);
	return (target != triggers.end());
}

std::list<ProximityTrigger*>::iterator
	Subscriber::get_trigger_iter(std::string const& trigger_id)
{
	std::list<ProximityTrigger*>::iterator target = triggers.end();
	for (auto iter = triggers.begin(); iter != triggers.end(); ++iter) {
		if ((*iter)->get_id() == trigger_id) {
			target = iter;
			break;
		}
	}
	return target;
}
