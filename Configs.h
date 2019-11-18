#ifndef CONFIGS_H
#define CONFIGS_H

#include <string>
#include <exception>

enum FilterType {
	RED		  = 0,
	BLUR	  = 1,
	EDGE	  = 2,
	THRESHOLD = 3,
	UNKNOWN	  = 4
};

class Configs {
private:
	static char const* filterTypes[];
	static std::exception const EXCEPTION_UNABLE_OPEN_FILE;
	static std::exception const EXCEPTION_INVALID_CONFIG;
	static std::exception const EXCEPTION_UNKNOWN_FILTER;
	static std::exception const EXCEPTION_NEGATIVE_BORDER;
	static std::exception const EXCEPTION_INVALID_BORDERS;

	int filterType;
	struct {
		int top;
		int bottom;
		int left;
		int right;
	} borders;

	void setFilterType(std::string filterTypeName);

public:
	explicit Configs(char const* configFilename);
	int getFilterType()   const { return filterType; }
	int getTopBorder()    const { return borders.top; }
	int getBottomBorder() const { return borders.bottom; }
	int getLeftBorder()   const { return borders.left; }
	int getRightBorder()  const { return borders.right; }
};

#endif /*CONFIGS_H*/