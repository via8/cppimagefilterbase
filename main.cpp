#include <iostream>
#include "png_toolkit.h"

void cstyle_test_filter(png_toolkit* studTool) {
	if (studTool == (png_toolkit*)NULL)
		throw "Null pointer passed";

	const int RGBcomp  = 3;
	const int RGBAcomp = 4;

	image_data imgData = studTool->getPixelData();

	if (imgData.pixels == (stbi_uc*)NULL ||
		imgData.h <= 0 || imgData.w <= 0 ||
		imgData.compPerPixel < RGBcomp)
		return;

	stbi_uc* imgEnd = imgData.pixels + imgData.h * imgData.w * imgData.compPerPixel;
	imgData.pixels += imgData.h / 2 * imgData.w * imgData.compPerPixel;

	for (; imgData.pixels < imgEnd; imgData.pixels += imgData.compPerPixel) {
		imgData.pixels[0] = 0xFF;
		imgData.pixels[1] = 0x00;
		imgData.pixels[2] = 0x00;
		if (imgData.compPerPixel == RGBAcomp)
			imgData.pixels[3] = 0xFF;
	}
}

int main(int argc, char * argv[]) {
    // toolkit filter_name base_pic_name student_tool student_pic_name limitPix limitMSE
    // toolkit near test images!
    try {
        if (argc != 3)
            throw "Not enough arguments";

        png_toolkit studTool;
        studTool.load(argv[1]);
		cstyle_test_filter(&studTool);
        studTool.save(argv[2]);

    } catch (const char * str) {
        std::cout << "Error: " << str << std::endl;
        return 1;
    }

    return 0;
}
