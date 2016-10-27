#include "input.h"
#include "utils.h"

#include <bitset>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <istream>
#include <iterator>
#include <string>
#include <vector>

#define ERROR_1(code) (std::cout << "[error]", (code))
#define ERROR ERROR_1(0)

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
			std::cin >> std::noskipws;

			std::istream_iterator<char> it(std::cin);
			std::istream_iterator<char> end;
			std::string input(it, end);

			utils::split_str(utils::trim_str(input, ::isspace), input_tokens, utils::pattern(" \n"), false);
		}
		if (input_tokens.size() > 0) {
			std::vector<std::string>::iterator it = input_tokens.begin();

			long long count;
			if (input::read(it++->c_str(), count)
				&& 0 < count && size_t(count) < input_tokens.size()) {

				values.reserve(count);

				double value;
				for (std::vector<std::string>::iterator it_end = input_tokens.end(); it != it_end; ++it) {
					if (input::read(it->c_str(), value)) {
						if (values.size() < size_t(count)) {
							values.push_back(value);
						}
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

		Sequence current = { 0, 0 }, max = { 0, 0 };
		for (std::vector<double>::size_type i = 1, imax = values.size(); i < imax; ++i) {
			if (values[i] >= values[i - 1]) {
				current.count++;
			} else {
				if (current.count > max.count) {
					max = current;
				}
				current.count = 0;
				current.location = i;
			}
		}
		if (current.count > max.count) {
			max = current;
		}
		if (max.count > 0) {
			std::cout << (max.count + 1) << ' ' << (max.location + 1);
		} else {
			std::cout << '0';
		}
	} else {
		return ERROR;
	}
	return 0;
}