#include "Configs.h"
#include <fstream>

char const* Configs::filterTypes[] = {
    "Red",
    "Blur",
    "Edge",
    "Threshold"
};
char const* Configs::EXCEPTION_INVALID_CONFIG	= "Invalid config's file content";
char const* Configs::EXCEPTION_UNKNOWN_FILTER   = "Unknown filter type name";
char const* Configs::EXCEPTION_NEGATIVE_BORDER  = "Negative border values are not allowed";
char const* Configs::EXCEPTION_INVALID_BORDERS  = "Invalid borders of rectangle specified";

void Configs::setFilterType(std::string filterTypeName) {
	int filtersQuantity = sizeof(filterTypes) / sizeof(char*);

	for (int filterNumber = 0; filterNumber < filtersQuantity; ++filterNumber)
		if (filterTypeName.compare(filterTypes[filterNumber]) == 0) {
			filterType = filterNumber;
			break;
		}
}

Configs::Configs(std::ifstream& configFile) :
    filterType(FilterType::UNKNOWN),
    borders{0,0,0,0} {

	std::string filterTypeName;
	if (!(configFile >> filterTypeName))
		return;

	if (!(configFile >> borders.top)	||
		!(configFile >> borders.left)	||
		!(configFile >> borders.bottom) ||
		!(configFile >> borders.right))
		throw Configs::EXCEPTION_INVALID_CONFIG;
	
	setFilterType(filterTypeName);
	if (filterType == FilterType::UNKNOWN)
		throw Configs::EXCEPTION_UNKNOWN_FILTER;

	if (borders.top    < 0 ||
		borders.left   < 0 ||
		borders.bottom < 0 ||
		borders.right  < 0)
		throw Configs::EXCEPTION_NEGATIVE_BORDER;

	// if values are not 0 we get rectangle with integer division
	// of image width/height by borders fields
	if ((borders.top  != 0 && borders.top  < borders.bottom) ||
		(borders.left != 0 && borders.left < borders.right))
		throw Configs::EXCEPTION_INVALID_BORDERS;
}
