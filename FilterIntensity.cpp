#include "FilterIntensity.h"
#include <cmath>

void FilterIntensity::runFilter(image_data& image, rectangle const& borders) const {
	for (int i = borders.top; i < borders.bottom; ++i) {
		stbi_uc* currPixel = image.pixels + (i * image.w + borders.left) * image.compPerPixel;
		for (int j = borders.left; j < borders.right; ++j) {
			stbi_uc intensity = currPixel[R] * 0.3 +
								currPixel[G] * 0.6 +
								currPixel[B] * 0.1;

			currPixel[R] = currPixel[G] = currPixel[B] = intensity;

			currPixel += image.compPerPixel;
		}
	}
}