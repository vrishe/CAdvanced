#ifndef UTILS_H_
#define UTILS_H_

#include <string>


#define CONCAT_(a, b) a##b
#define CONCAT(a, b) CONCAT_(a, b)


namespace utils {

template <typename TContainer>
	static split_str(const std::string &str, TContainer &output, 
		const std::string &delim = " ", bool removeEmpty = true) {

		typedef typename TContainer::value_type ValueType; 
		typedef typename TContainer::size_type  SizeType;

		std::string::size_type pos, pos_prev = 0, length = str.length();

		while (pos_prev <= length) {
			pos = str.find_first_of(delim, pos_prev);

			if (pos == std::string::npos) {
				pos = length;
			}
			if (pos != pos_prev || !removeEmpty) {
				output.push_back(ValueType(&str[pos_prev],
					static_cast<SizeType>(pos - pos_prev)));
			}
			pos_prev = pos + 1;
		}
	}

}

#endif // UTILS_H_