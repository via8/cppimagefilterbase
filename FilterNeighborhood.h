#ifndef FILTER_NEIGHBORHOOD_H
#define FILTER_NEIGHBORHOOD_H

#include "Filter.h"

class FilterNeighborhood : virtual public Filter {
private:
	static char const* EXCEPTION_INAPPROPRIATE_DIM;

	// conversion of specified pixel according to it's neighborhood
	virtual void conversion(stbi_uc const* matrix, stbi_uc* pixel, int compPerPixel, int matrixWidth, int i, int j) const = 0;

protected:
	// positive odd integer value - dimension of neighborhood square matrix
	int neighborhoodDim;

	// half of conversion matrix dimension excluding it's center
	int extraRegionSize;

	void runFilter(image_data& image, rectangle const& borders) const;

public:
	explicit FilterNeighborhood(Configs const& configs, int neighborhoodDim);
	~FilterNeighborhood() {}
};

#endif /*FILTER_NEIGHBORHOOD_H*/
