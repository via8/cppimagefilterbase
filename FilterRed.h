#ifndef FILTER_RED_H
#define FILTER_RED_H

#include "Filter.h"

class FilterRed : public Filter {
private:
	void runFilter(image_data& image, rectangle const& borders) const;

public:
	explicit FilterRed(Configs const& configs) : Filter(configs) {}
	~FilterRed() {}
};

#endif /*FILTER_RED_H*/