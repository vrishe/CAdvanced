#include "input.h"

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <string>

namespace input {

	bool read_impl(const char *str, size_t str_size, double &result) {
		if (str_size > 0) {
			bool negative = false;

			if (str_size > 1) {
				char inputChar = *str;

				if (inputChar == '+'
					|| (negative = inputChar == '-')) {

					--str_size;
					++str;
				}
			}
		}
		return false;
	}

	bool read(const char *str, double &result) {
		return read_impl(str, strlen(str), result);
	}


	bool read_impl(const char *str, size_t str_size, long long &result) {
		if (str_size > 0) {
			long long rank = 1;

			static const char validChars[] = "0123456789+";
			for (size_t i = str_size - 2; i < str_size; --i) {
				bool correct = false;

				for (size_t j = 0, jmax = sizeof(validChars) - 1; j < jmax; ++j) {
					char inputChar = str[i];

					if (inputChar == validChars[j]) {
						if (j < 10) {
							result += j * rank;
							rank *= 10;

							correct = true;
							break;
						}
						else if (i == 0) {
							correct = true;
							break;
						}
					}
				}
				if (!correct) {
					return false;
				}
			}
			return true;
		}
		return false;
	}

	bool read(const char *str, long long &result) {
		return read_impl(str, strlen(str), result);
	}


	std::istream &read(std::istream &src, long long &result) {
		result = 0;

		char input[] = "+9223372036854775807";
		size_t countRead = src
			.getline(input, sizeof(input))
			.gcount();

		src.clear();

		if (!read_impl(input, countRead, result)) {
			src.setstate(std::ios_base::failbit);
		}
		return src;
	}


	namespace {
		std::istream &read_impl(std::istream &src, long long *result) {
			return read(src, *result);
		}
	}

	ISMANIP<long long*> read(long long &result) {
		return ISMANIP<long long*>(read_impl, &result);
	}
}