#include "input.h"
#include "countof.h"

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <string>


namespace input {

	namespace _double {

		struct MatchRule {

			bool (*matcher_func)(char character, size_t count);

			size_t next_rule;

		};

		static bool digit_matcher(char character, size_t count) {
			return '0' <= character && character <= '9';
		}

		static bool exponent_matcher(char character, size_t count) {
			return character == 'e' || character == 'E';
		}

		static bool dot_matcher(char character, size_t count) {
			return character == '.';
		}

		static bool sign_matcher(char character, size_t count) {
			return count > 1 && (character == '-' || character == '+');
		}


		bool read(const char *str, size_t str_size, double &result) {
			static const MatchRule rules[] = { 
				{ sign_matcher, 1 },
				{ digit_matcher, 1 },
				{ dot_matcher, 3 },
				{ digit_matcher, 3 },
				{ exponent_matcher, 5 },
				{ sign_matcher, 6 },
				{ digit_matcher, 6 }
			};
			std::string input;

			size_t index = 0;
			while (str_size > 0) {
				bool matches = false;

				do {
					if (rules[index].matcher_func(*str, str_size)) {
						index = rules[index].next_rule;
						matches = true;

						break;
					}
				} while (++index < countof(rules));

				if (matches) {
					input.push_back(*str);

					++str;
					--str_size;
				} else {
					return false;
				}
			}
			result = strtod(input.c_str(), NULL);

			return true;
		}
	}


	bool read(const char *str, double &result) {
		return _double::read(str, strlen(str), result);
	}


	namespace _long_long {

		bool read(const char *str, size_t str_size, long long &result) {
			static const char validChars[] = "0123456789+";

			long long output = 0, rank = 1;
			for (size_t i = str_size - 1; i < str_size; --i) {
				bool correct = false;

				for (size_t j = 0, jmax = countof(validChars) - 1; j < jmax; ++j) {
					char inputChar = str[i];

					if (inputChar == validChars[j]) {
						if (j < 10) {
							output += j * rank;
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
			result = output;

			return true;
		}
	}

	bool read(const char *str, long long &result) {
		return _long_long::read(str, strlen(str), result);
	}


	std::istream &read(std::istream &src, long long &result) {
		result = 0;

		char input[] = "+9223372036854775807";
		size_t countRead = src
			.getline(input, countof(input))
			.gcount();

		src.clear();

		if (countRead <= 0 || !_long_long::read(input, countRead - 1, result)) {
			src.setstate(std::ios_base::failbit);
		}
		return src;
	}


	std::istream &read_manip(std::istream &src, long long *result) {
		return read(src, *result);
	}

	ISMANIP<long long*> read(long long &result) {
		return ISMANIP<long long*>(read_manip, &result);
	}
}