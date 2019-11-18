#include "FilterEdge.h"

FilterEdge::FilterEdge(Configs const& configs) :
	Filter(configs),
	FilterIntensity(configs),
	FilterNeighborhood(configs, 3),
	centerMultiplier(neighborhoodDim * neighborhoodDim),
	edgeMultiplier(-1) {}

void FilterEdge::conversion(stbi_uc const* matrix, stbi_uc* pixel, int compPerPixel, int matrixWidth, int i, int j) const {
	// initialize new values of channels with 0
	int compR = 0;
	int compG = 0;
	int compB = 0;

	// start calculation of conversion value for each channel
	for (int row = -extraRegionSize; row <= extraRegionSize; ++row) {
		for (int col = -extraRegionSize; col <= extraRegionSize; ++col) {
			int shift = ((i + extraRegionSize + row) * matrixWidth + (j + extraRegionSize + col)) * compPerPixel;
			if (row == 0 && col == 0) {
				compR += (matrix + shift)[R] * centerMultiplier;
				compG += (matrix + shift)[G] * centerMultiplier;
				compB += (matrix + shift)[B] * centerMultiplier;
			}
			else {
				compR += (matrix + shift)[R] * edgeMultiplier;
				compG += (matrix + shift)[G] * edgeMultiplier;
				compB += (matrix + shift)[B] * edgeMultiplier;
			}
		}
	}

	// get stbi_uc values
	// TODO: replace magic number 255
	pixel[R] = (compR > 255) ? 255 : ((compR < 0) ? 0 : (stbi_uc)compR);
	pixel[G] = (compR > 255) ? 255 : ((compG < 0) ? 0 : (stbi_uc)compG);
	pixel[B] = (compR > 255) ? 255 : ((compB < 0) ? 0 : (stbi_uc)compB);
}

void FilterEdge::runFilter(image_data& image, rectangle const& borders) const {
	   FilterIntensity::runFilter(image, borders);
	FilterNeighborhood::runFilter(image, borders);
}