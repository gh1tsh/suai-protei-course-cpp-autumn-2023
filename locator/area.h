//
// Created by ghitsh on 23.11.23.
//

#ifndef LOCATOR_AREA_H
#define LOCATOR_AREA_H


#include <string>
#include <utility>


class Area {
public:


private:
	unsigned id;
	std::string name;
	std::pair<int, int> location;
	unsigned radius; // Radius of an area
};


#endif //LOCATOR_AREA_H
