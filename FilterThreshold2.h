#ifndef FILTER_THRESHOLD2_H
#define FILTER_THRESHOLD2_H

#include "FilterIntensity.h"

class FilterThreshold2 : public FilterIntensity {
private:
	static char const* EXCEPTION_INAPPROPRIATE_DIM;
	static char const* EXCEPTION_RUNTIME_ALLOCATION;

	int squareDim;

	// half of square dimension excluding it's center
	int extraRegionSize;

	void threshold(stbi_uc const* matrix, stbi_uc* pixel, int compPerPixel, int matrixWidth, int i, int j, rectangle const& squareBorders) const;

protected:
	void runFilter(image_data& image, rectangle const& borders) const;

public:
	explicit FilterThreshold2(Configs const& configs);
	~FilterThreshold2() {}
};

#endif /*FILTER_THRESHOLD2_H*/
