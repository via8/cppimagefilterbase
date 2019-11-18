#ifndef FILTER_THRESHOLD_H
#define FILTER_THRESHOLD_H

#include "FilterIntensity.h"
#include "FilterNeighborhood.h"

class FilterThreshold : public FilterIntensity, public FilterNeighborhood {
private:
	void conversion(stbi_uc const* matrix, stbi_uc* pixel, int compPerPixel, int matrixWidth, int i, int j) const;

protected:
	void runFilter(image_data& image, rectangle const& borders) const;

public:
	explicit FilterThreshold(Configs const& configs);
	~FilterThreshold() {}
};

#endif /*FILTER_THRESHOLD_H*/