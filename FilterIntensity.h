#ifndef FILTER_INTENSITY_H
#define FILTER_INTENSITY_H

#include "Filter.h"

class FilterIntensity : virtual public Filter {
private:
	float intensityProportionR = 0.3f;
	float intensityProportionG = 0.6f;
	float intensityProportionB = 0.1f;

protected:
	void runFilter(image_data& image, rectangle const& borders) const;

public:
	explicit FilterIntensity(Configs const& configs) : Filter(configs) {}
	~FilterIntensity() {}
};

#endif /*FILTER_INTENSITY_H*/