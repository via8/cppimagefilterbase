#include <iostream>
#include <exception>
#include "png_toolkit.h"
#include "Configs.h"
#include "Filter.h"
#include "FilterRed.h"
#include "FilterBlur.h"
#include "FilterEdge.h"
#include "FilterThreshold.h"
#include "FilterThreshold2.h"

int main(int argc, char * argv[]) {
    try {
        if (argc != 4)
            throw "Not enough arguments";

		Configs configs(argv[1]);

		Filter* filter = nullptr;
		switch (configs.getFilterType()) {
		case FilterType::RED:
			filter = new FilterRed(configs);
			break;
		case FilterType::BLUR:
			filter = new FilterBlur(configs);
			break;
		case FilterType::EDGE:
			filter = new FilterEdge(configs);
			break;
		case FilterType::THRESHOLD:
			//filter = new FilterThreshold(configs);
			filter = new FilterThreshold2(configs);
			break;
		default:
			break;
		}

		if (filter != nullptr) {
			png_toolkit studTool;
			studTool.load(argv[2]);
			image_data image = studTool.getPixelData();
			filter->processPNG(image);
			studTool.save(argv[3]);
		}

    } catch (char const* err) {
        std::cout << "Error: " << err << std::endl;
        return 1;
    }

    return 0;
}
