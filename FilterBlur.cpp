#include "FilterBlur.h"
#include <stdlib.h>

FilterBlur::FilterBlur(Configs const& configs) :
	Filter(configs),
	FilterNeighborhood(configs, 3),
	normalizationDivider(neighborhoodDim * neighborhoodDim) {}

void FilterBlur::conversion(stbi_uc const* matrix, stbi_uc* pixel, int compPerPixel, int matrixWidth, int i, int j) const {
	// initialize new values of channels with 0
	int compR = 0;
	int compG = 0;
	int compB = 0;

	// start calculation of conversion value for each channel
	for (int row = -extraRegionSize; row <= extraRegionSize; ++row) {
		for (int col = -extraRegionSize; col <= extraRegionSize; ++col) {
			int shift = ((i + extraRegionSize + row) * matrixWidth + (j + extraRegionSize + col)) * compPerPixel;
			compR += (matrix + shift)[R];
			compG += (matrix + shift)[G];
			compB += (matrix + shift)[B];
		}
	}

	// get stbi_uc values
	pixel[R] = (stbi_uc)(compR / normalizationDivider);
	pixel[G] = (stbi_uc)(compG / normalizationDivider);
	pixel[B] = (stbi_uc)(compB / normalizationDivider);
}