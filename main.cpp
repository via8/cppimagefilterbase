#include <iostream>
#include <fstream>
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

		std::ifstream configFile;
		configFile.open(argv[1], std::ifstream::in);
		if (!configFile.is_open())
			throw "Unable to open file";

		png_toolkit studTool;
		studTool.load(argv[2]);
		while (!configFile.eof()) {

			Configs configs(configFile);

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
				image_data image = studTool.getPixelData();
				filter->processPNG(image);
			}
		}

		studTool.save(argv[3]);
		configFile.close();

    } catch (char const* err) {
        std::cout << "Error: " << err << std::endl;
        return 1;
    }

    return 0;
}
