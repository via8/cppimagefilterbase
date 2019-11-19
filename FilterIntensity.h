#ifndef FILTER_INTENSITY_H
#define FILTER_INTENSITY_H

#include "Filter.h"

class FilterIntensity : virtual public Filter {
private:
	int intensityCoeffR = 3;
	int intensityCoeffG = 6;
	int intensityCoeffB = 1;
	int normalizationCoeff = 10;

protected:
	void runFilter(image_data& image, rectangle const& borders) const;

public:
	explicit FilterIntensity(Configs const& configs) : Filter(configs) {}
	~FilterIntensity() {}
};

#endif /*FILTER_INTENSITY_H*/