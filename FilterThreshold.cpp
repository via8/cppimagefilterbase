#include "FilterThreshold.h"
#include <vector>
#include <algorithm>

FilterThreshold::FilterThreshold(Configs const& configs) :
	Filter(configs),
	FilterIntensity(configs),
	FilterNeighborhood(configs, 5) {}


void FilterThreshold::conversion(stbi_uc const* matrix, stbi_uc* pixel, int compPerPixel, int matrixWidth, int i, int j) const {
	// initialize vector of current square intensities
	int squareSize = neighborhoodDim * neighborhoodDim;
	stbi_uc* square = new stbi_uc[squareSize];

	// fill vector with intensities
	for (int k = 0, row = -extraRegionSize; row <= extraRegionSize; ++row) {
		for (int col = -extraRegionSize; col <= extraRegionSize; ++col) {
			int shift = ((i + extraRegionSize + row) * matrixWidth + (j + extraRegionSize + col)) * compPerPixel;
			square[k++] = (matrix + shift)[R];
		}
	}

	std::sort(square, square + squareSize);

	// threshold process: compare current pixel intensity with median value of the square
	if (pixel[R] < square[squareSize / 2])
		pixel[R] = pixel[G] = pixel[B] = 0x0;

	delete[] square;
}

void FilterThreshold::runFilter(image_data& image, rectangle const& borders) const {
	   FilterIntensity::runFilter(image, borders);
	FilterNeighborhood::runFilter(image, borders);
}