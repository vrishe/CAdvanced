#include "input.h"
#include "countof.h"

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <string>


namespace input {

	namespace _double {

		struct MatchRule {

			bool (*matcher_func)(char character);

			size_t next_rule;

			size_t exit_rule;

		};

		static bool digit_matcher(char character) {
			return '0' <= character && character <= '9';
		}

		static bool exponent_matcher(char character) {
			return character == 'e' || character == 'E';
		}

		static bool dot_matcher(char character) {
			return character == '.';
		}

		static bool sign_matcher(char character) {
			return character == '-' || character == '+';
		}


		bool read(const char *str, size_t str_size, double &result) {
			if (str_size) {
				std::string input;
				{
					static const MatchRule rules[] = { 
						{ sign_matcher, 1, 2 },				// 0
						{ digit_matcher, 2, size_t(-1) },	// 1
						{ digit_matcher, 2, 3 },			// 2
						{ dot_matcher, 4, 5 },				// 3
						{ digit_matcher, 5, size_t(-1) },	// 4
						{ digit_matcher, 5, 6 },			// 5
						{ exponent_matcher, 7, 9 },			// 6
						{ sign_matcher, 8, 9 },				// 7
						{ digit_matcher, 9, size_t(-1) },	// 8
						{ digit_matcher, 9, size_t(-1) }	// 9
					};
					for (size_t i = 0; str_size > 0;) {
						for (;;) {
							const MatchRule &rule = rules[i];

							if (rule.matcher_func(*str)) {
								input.push_back(*str++);
								i = rule.next_rule;
								--str_size;

								break;
							} else {
								i = rule.exit_rule;
							}
							if (i >= countof(rules)) {
								return false;
							}
						}
					}
				}
				result = strtod(input.c_str(), NULL);

				return true;
			}
			return false;
		}
	}


	bool read(const char *str, double &result) {
		return _double::read(str, strlen(str), result);
	}


	namespace _long_long {

		bool read(const char *str, size_t str_size, long long &result) {
			static const char validChars[] = "0123456789+";

			if (str_size) {
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
			return false;
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