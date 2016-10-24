#include "input.h"
#include "utils.h"

#include <bitset>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#define ERROR_1(code) (std::cout << "[error]", (code))
#define ERROR ERROR_1(-1)

int main (int argc, char *argv[]) {
	std::vector<double> values;

	if (argc > 1) {
		if (!strcmp(argv[1], "-i")) {
			values.reserve(argc - 2);

			double value;
			for (int i = 2; i < argc; ++i) {
				if (input::read(argv[i], value)) {
					values.push_back(value);
				} else {
					return ERROR_1(-201);
				}
			}
		} else {
			return ERROR;
		}
	} else {
		std::vector<std::string> input_tokens;
		{
			std::string input;

			std::getline(std::cin, input);
			utils::split_str(input, input_tokens);
		}
		if (input_tokens.size() > 0) {
			std::vector<std::string>::iterator it = input_tokens.begin();

			long long count;
			if (input::read(it++->c_str(), count)
				&& 0 < count && count < input_tokens.size()) {

				values.reserve(count);

				double value;
				for (std::vector<std::string>::iterator it_end = input_tokens.end(); 
					it != it_end; ++it) {

					if (input::read(it->c_str(), value)) {
						values.push_back(value);
					} else {
						return ERROR;
					}
				}
			} else {
				return ERROR;
			}
		}
	}
	if (values.size() >= 2) {
		struct Sequence {
			size_t count;

			std::vector<double>::size_type location;
		};

		Sequence current = { 1, 0 }, max = { 0, 0 };
		for (std::vector<double>::size_type i = 1, imax = values.size(); i < imax; ++i) {
			if (values[i] >= values[i - 1]) {
				current.count++;
			} else {
				if (current.count > max.count) {
					max = current;
				}
				current.count = 1;
				current.location = i;
			}
		}
		if (current.count > max.count) {
			max = current;
		}
		std::cout << max.count;

		if (max.count > 0) {
			std::cout << ' ' << (max.location + 1);
		}
		std::cout << std::endl;
	} else {
		return ERROR;
	}
	return 0;
}