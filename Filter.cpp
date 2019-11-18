#include "Filter.h"

char const* Filter::EXCEPTION_INAPPROPRIATE_IMAGE = "Inappropriate image data";

void Filter::processPNG(image_data& image) const {
	if (image.pixels == NULL ||
		image.h <= 0 ||
		image.w <= 0 ||
		image.compPerPixel < RGBcomp ||
		image.compPerPixel > RGBAcomp)
		throw Filter::EXCEPTION_INAPPROPRIATE_IMAGE;

	rectangle borders = {
		(configs.getTopBorder()    == 0) ? 0 : image.h / configs.getTopBorder(),
		(configs.getBottomBorder() == 0) ? 0 : image.h / configs.getBottomBorder(),
		(configs.getLeftBorder()   == 0) ? 0 : image.w / configs.getLeftBorder(),
		(configs.getRightBorder()  == 0) ? 0 : image.w / configs.getRightBorder(),
	};

	runFilter(image, borders);
}
