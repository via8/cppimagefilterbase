#include "FilterRed.h"

void FilterRed::runFilter(image_data& image, rectangle const& borders) const {
	for (int i = borders.top; i < borders.bottom; ++i) {
		stbi_uc* currPixel = image.pixels + (i * image.w + borders.left) * image.compPerPixel;
		for (int j = borders.left; j < borders.right; ++j) {
			currPixel[R] = 0xFF;	// R channel
			currPixel[G] = 0x00;	// G channel
			currPixel[B] = 0x00;	// B channel
			
			currPixel += image.compPerPixel;
		}
	}
}