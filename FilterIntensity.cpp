#include "FilterIntensity.h"

void FilterIntensity::runFilter(image_data& image, rectangle const& borders) const {
	for (int i = borders.top; i < borders.bottom; ++i) {
		stbi_uc* currPixel = image.pixels + (i * image.w + borders.left) * image.compPerPixel;
		for (int j = borders.left; j < borders.right; ++j) {
			float value = currPixel[0] * intensityProportionR +
						  currPixel[1] * intensityProportionG +
						  currPixel[2] * intensityProportionB;

			currPixel[0] = (stbi_uc)value;	// R channel
			currPixel[1] = (stbi_uc)value;	// G channel
			currPixel[2] = (stbi_uc)value;	// B channel

			currPixel += image.compPerPixel;
		}
	}
}