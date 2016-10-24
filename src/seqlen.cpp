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
		// TODO: find the sequence length here.
	} else {
		return ERROR;
	}
	return 0;
}