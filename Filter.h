#ifndef FILTER_H
#define FILTER_H

#include <exception>
#include "Configs.h"
#include "png_toolkit.h"

struct rectangle {
	int top;
	int bottom;
	int left;
	int right;
};

class Filter {
private:
	static std::exception const EXCEPTION_INAPPROPRIATE_IMAGE;

	int const RGBcomp  = 3;		// RGB  channels
	int const RGBAcomp = 4;		// RGBA channels

	Configs const& configs;

protected:
	enum ColorChannels {
		R = 0,	// red   channel index
		G = 1,	// green channel index
		B = 2	// blue  channel index
	};

	virtual void runFilter(image_data& image, rectangle const& borders) const = 0;

public:
	explicit Filter(Configs const& configs) : configs(configs) {}
	virtual ~Filter() {};
	void processPNG(image_data& image) const;
};

#endif /*FILTER_H*/