#ifndef FILTER_EDGE_H
#define FILTER_EDGE_H

#include "FilterIntensity.h"
#include "FilterNeighborhood.h"

class FilterEdge : public FilterIntensity, public FilterNeighborhood {
private:
	// edge normalization multipliers for conversion process
	int centerMultiplier;
	int edgeMultiplier;

	// convolution normalization divider for conversion process
	int const normalizationDivider;

	void conversion(stbi_uc const* matrix, stbi_uc* pixel, int compPerPixel, int matrixWidth, int i, int j) const;

protected:
	void runFilter(image_data& image, rectangle const& borders) const;

public:
	explicit FilterEdge(Configs const& confings);
	~FilterEdge() {}
};

#endif /*FILTER_EDGE_H*/