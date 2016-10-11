#include "manip.h"


#ifndef INPUT_H_
#define INPUT_H_


#include <istream>

namespace input {

	bool read(const char *str, double &result);

	bool read(const char *str, long long &result);


	std::istream &read(std::istream &src, long long &result);


	ISMANIP<long long*> read(long long &result);
}


#endif // INPUT_H_