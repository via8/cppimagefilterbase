#include "FilterEdge.h"

FilterEdge::FilterEdge(Configs const& configs) :
	Filter(configs),
	FilterIntensity(configs),
	FilterNeighborhood(configs, 3),
	centerMultiplier(neighborhoodDim * neighborhoodDim),
	edgeMultiplier(-1) {}

void FilterEdge::conversion(stbi_uc const* matrix, stbi_uc* pixel, int compPerPixel, int matrixWidth, int i, int j) const {
	// initialize initial intensity value with 0
	int intensity = 0;

	// start calculation of conversion value for each channel
	for (int row = -extraRegionSize; row <= extraRegionSize; ++row) {
		for (int col = -extraRegionSize; col <= extraRegionSize; ++col) {
			int shift = ((i + extraRegionSize + row) * matrixWidth + (j + extraRegionSize + col)) * compPerPixel;
			if (row == 0 && col == 0) {
				intensity += (matrix + shift)[R] * centerMultiplier;
			}
			else {
				intensity += (matrix + shift)[R] * edgeMultiplier;
			}
		}
	}

	// get stbi_uc value
	// TODO: replace magic number 255
	pixel[R] = pixel[G] = pixel[B] = (intensity > 255) ? 255 : ((intensity < 0) ? 0 : (stbi_uc)intensity);
}

void FilterEdge::runFilter(image_data& image, rectangle const& borders) const {
	   FilterIntensity::runFilter(image, borders);
	FilterNeighborhood::runFilter(image, borders);
}