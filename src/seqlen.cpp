#include "input.h"
#include "utils.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#define ERROR_1(code) (std::cout << "[error]", (code))
#define ERROR ERROR_1(-1)

int main (int argc, char *argv[]) {
	std::vector<double> values;

	if (argc > 1) {
		if (!strcmp(argv[1], "-i")) {
			values.reserve(argc - 2);

			for (int i = 2; i < argc; ++i) {

			}
		} else {
			return ERROR;
		}
	}
	return 0;
}