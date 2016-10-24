#include "input.h"

#include <cerrno>
#include <cmath>
#include <cstdio>
#include <iostream>

#define SQRT2 1.4142135623731

static bool trinum(long long t, long long &result) {
	if (t > 0) {
		result = (long long)(sqrt(t) * SQRT2);

		return t / result == (result + 1) / 2;		
	}
	return false;
}

int main() {
	long long result, t;

	std::cin >> input::read(t);

	if (!std::cin.fail() && trinum(t, result)) {
		std::cout << result;
	} else {
		std::cout << 0;	
	}
	return 0;
}