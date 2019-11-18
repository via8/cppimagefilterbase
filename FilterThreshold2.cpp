#include "FilterThreshold2.h"
#include <algorithm>
#include <cstring>

char const* FilterThreshold2::EXCEPTION_INAPPROPRIATE_DIM  = "FilterNeighborhood dimension must be odd natual number >= 3";
char const* FilterThreshold2::EXCEPTION_RUNTIME_ALLOCATION = "Another square size non-positive value. Unknown error.";

FilterThreshold2::FilterThreshold2(Configs const& configs) :
	Filter(configs),
	FilterIntensity(configs),
	squareDim(5),
	extraRegionSize(squareDim / 2) {}

void FilterThreshold2::threshold(stbi_uc const* matrix, stbi_uc* pixel, int compPerPixel, int matrixWidth, int i, int j, rectangle const& squareBorders) const {
	// initialize vector of current square intensities
	int squareSize = (squareBorders.bottom - squareBorders.top) * (squareBorders.right - squareBorders.left);

	if (squareSize <= 0)
		throw FilterThreshold2::EXCEPTION_RUNTIME_ALLOCATION;

	stbi_uc* square = new stbi_uc[squareSize];

	// fill vector with intensities
	for (int k = 0, row = squareBorders.top - i; row < squareBorders.bottom - i; ++row) {
		for (int col = squareBorders.left - j; col < squareBorders.right - j; ++col) {
			int shift = ((i + row) * matrixWidth + (j + col)) * compPerPixel;
			square[k++] = (matrix + shift)[R];
		}
	}

	std::sort(square, square + squareSize);

	// threshold process: compare current pixel intensity with median value of the square
	if (pixel[R] < square[squareSize / 2])
		pixel[R] = pixel[G] = pixel[B] = 0x0;

	delete[] square;
}

void FilterThreshold2::runFilter(image_data& image, rectangle const& borders) const {
	// pre-process image with intensity filter
	FilterIntensity::runFilter(image, borders);

	// linear dimensions of processed rectangle
	int rectangleH = borders.bottom - borders.top;
	int rectangleW = borders.right - borders.left;

	// memory allocation for initial matrix of pixels
	size_t pixelSize = sizeof(stbi_uc) * image.compPerPixel;
	stbi_uc* matrix = new stbi_uc[rectangleH * rectangleW * pixelSize];

	// fill initial matrix of pixels
	for (int i = borders.top, row = 0; i < borders.bottom; ++i, ++row) {
		for (int j = borders.left, col = 0; j < borders.right; ++j, ++col) {
			memcpy(matrix + (row * rectangleW + col) * image.compPerPixel,
						image.pixels + (i * image.w + j) * image.compPerPixel, pixelSize);
		}
	}

	// start conversion procces by calling conversion method for each pixel of processed rectangle
	for (int i = 0; i < rectangleH; ++i) {
		stbi_uc* currPixel = image.pixels + ((i + borders.top) * image.w + borders.left) * image.compPerPixel;
		for (int j = 0; j < rectangleW; ++j) {

			rectangle squareBorders = {
				std::max(0, i - extraRegionSize),					// top
				std::min(borders.bottom, i + extraRegionSize + 1),	// bot
				std::max(0, j - extraRegionSize),					// left
				std::min(borders.right,  j + extraRegionSize + 1)	// right
			};

			threshold(matrix, currPixel, image.compPerPixel, rectangleW, i, j, squareBorders);

			// next pixel
			currPixel += image.compPerPixel;
		}
	}

	delete[] matrix;
}
