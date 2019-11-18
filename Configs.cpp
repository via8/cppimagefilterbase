#include "Configs.h"
#include <fstream>

char const* Configs::filterTypes[] = {
    "Red",
    "Blur",
    "Edge",
    "Threshold"
};
std::exception const Configs::EXCEPTION_UNABLE_OPEN_FILE = std::exception("Unable to open file");
std::exception const Configs::EXCEPTION_INVALID_CONFIG	 = std::exception("Invalid config's file content");
std::exception const Configs::EXCEPTION_UNKNOWN_FILTER   = std::exception("Unknown filter type name");
std::exception const Configs::EXCEPTION_NEGATIVE_BORDER  = std::exception("Negative border values are not allowed");
std::exception const Configs::EXCEPTION_INVALID_BORDERS  = std::exception("Invalid borders of rectangle specified");

void Configs::setFilterType(std::string filterTypeName) {
	int filtersQuantity = sizeof(filterTypes) / sizeof(char*);

	for (int filterNumber = 0; filterNumber < filtersQuantity; ++filterNumber)
		if (filterTypeName.compare(filterTypes[filterNumber]) == 0) {
			filterType = filterNumber;
			break;
		}
}

Configs::Configs(char const* configFilename) :
    filterType(FilterType::UNKNOWN),
    borders{0,0,0,0} {
	std::ifstream configFile;
	configFile.open(configFilename, std::ifstream::in);

	if (!configFile.is_open())
		throw Configs::EXCEPTION_UNABLE_OPEN_FILE;

	std::string filterTypeName;
	if (!(configFile >> filterTypeName) ||
		!(configFile >> borders.top)	||
		!(configFile >> borders.left)	||
		!(configFile >> borders.bottom) ||
		!(configFile >> borders.right))
		throw Configs::EXCEPTION_INVALID_CONFIG;

	configFile.close();

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