#ifndef MANIP_H_
#define MANIP_H_

#include <istream>


template <typename T>
class ISMANIP {

public:
	typedef std::istream &(*manip_func)(std::istream&, T);


	friend std::istream &operator >> (std::istream &s, const ISMANIP &m) { 
		return (*m.action)(s, m.value);
	}

	ISMANIP(manip_func action, T value)
		: action(action), value(value) { }

private:
	T value;
	manip_func action;
};

#endif // MANIP_H_