#include "FilterNeighborhood.h"

std::exception const FilterNeighborhood::EXCEPTION_INAPPROPRIATE_DIM = std::exception("FilterNeighborhood dimension must be odd natual number >= 3");

FilterNeighborhood::FilterNeighborhood(Configs const& configs, int neighborhoodDim) :
	Filter(configs),
	neighborhoodDim(neighborhoodDim),
	extraRegionSize(neighborhoodDim / 2) {}

void FilterNeighborhood::runFilter(image_data& image, rectangle const& borders) const {
	if (neighborhoodDim < 3 || neighborhoodDim % 2 == 0)
		throw FilterNeighborhood::EXCEPTION_INAPPROPRIATE_DIM;

	// linear dimensions of processed rectangle
	int rectangleH = borders.bottom - borders.top;
	int rectangleW = borders.right  - borders.left;

	// linear dimensions of initial matrix of pixels used during conversion process
	int matrixH = rectangleH + 2 * extraRegionSize;
	int matrixW = rectangleW + 2 * extraRegionSize;

	// memory allocation for initial matrix of pixels
	size_t pixelSize = sizeof(stbi_uc) * image.compPerPixel;
	stbi_uc* matrix = new stbi_uc[matrixH * matrixW * pixelSize];

	// initial matrix borders
	rectangle matrixBorders = {
		borders.top    - extraRegionSize,
		borders.bottom + extraRegionSize,
		borders.left   - extraRegionSize,
		borders.right  + extraRegionSize
	};

	// fill initial matrix of pixels
	for (int i = matrixBorders.top, row = 0; i < matrixBorders.bottom; ++i, ++row) {
		// if vertical size out of image borders then fill whole row of pixels with 0
		if (row < extraRegionSize || row >= rectangleH + extraRegionSize)
			std::memset(matrix + row * matrixW * image.compPerPixel, 0, matrixW * pixelSize);
		else
			for (int j = matrixBorders.left, col = 0; j < matrixBorders.right; ++j, ++col) {
				// if horizontal size out of image borders then fill current pixel with 0
				if (col < extraRegionSize || col >= rectangleW + extraRegionSize)
					std::memset(matrix + (row * matrixW + col) * image.compPerPixel, 0, pixelSize);
				// else copy initial pixel
				else
					std::memcpy(matrix + (row * matrixW + col) * image.compPerPixel,
						image.pixels + (i * image.w + j) * image.compPerPixel, pixelSize);
			}
	}

	// start conversion procces by calling conversion method for each pixel of processed rectangle
	for (int i = 0; i < rectangleH; ++i) {
		stbi_uc* currPixel = image.pixels + ((i + borders.top) * image.w + borders.left) * image.compPerPixel;
		for (int j = 0; j < rectangleW; ++j) {
			// execute conversion for i,j pixel
			conversion(matrix, currPixel, image.compPerPixel, matrixW, i, j);

			// next pixel
			currPixel += image.compPerPixel;
		}
	}

	delete[] matrix;
}