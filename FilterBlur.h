#ifndef FILTER_BLUR_H
#define FILTER_BLUR_H

#include "FilterNeighborhood.h"

class FilterBlur : public FilterNeighborhood {
private:
	// blur normalization divider for conversion process
	int const normalizationDivider;

	void conversion(stbi_uc const* matrix, stbi_uc* pixel, int compPerPixel, int matrixWidth, int i, int j) const;

public:
	explicit FilterBlur(Configs const& configs);
	~FilterBlur() {}
};

#endif /*FILTER_BLUR_H*/