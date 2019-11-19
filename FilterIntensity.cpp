#include "FilterIntensity.h"
#include <cmath>

void FilterIntensity::runFilter(image_data& image, rectangle const& borders) const {
	for (int i = borders.top; i < borders.bottom; ++i) {
		stbi_uc* currPixel = image.pixels + (i * image.w + borders.left) * image.compPerPixel;
		for (int j = borders.left; j < borders.right; ++j) {

			stbi_uc intensity = (currPixel[R] * intensityCoeffR +
								 currPixel[G] * intensityCoeffG +
								 currPixel[B] * intensityCoeffB) / 
								 normalizationCoeff;

			currPixel[R] = currPixel[G] = currPixel[B] = intensity;

			currPixel += image.compPerPixel;
		}
	}
}