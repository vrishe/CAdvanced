#ifndef UTILS_H_
#define UTILS_H_

#include <algorithm>
#include <cstdarg>
#include <cstring>
#include <functional>
#include <string>


#define CONCAT_(a, b) a##b
#define CONCAT(a, b) CONCAT_(a, b)

#define FOR_EACH(it, container) \
	for (auto it = (container).begin(), it##_end = (container).end(); it != it##_end; ++it)

namespace utils {

	template<typename TIter>
	class Pattern : public std::unary_function<char, bool> {
		TIter start, end;

	public:
		Pattern(TIter start, TIter end)
			: start(start), end(end) { }

		bool operator() (char value) const { 
			return std::find(start, end, value) != end; 
		}
	};

	Pattern<std::string::const_iterator> pattern(const std::string &src) {
		return Pattern<std::string::const_iterator>(src.begin(), src.end());
	}

	Pattern<const char*> pattern(const char *src) {
		return Pattern<const char*>(src, src + strlen(src));
	}

	Pattern<const char*> pattern(const char src[], size_t length, size_t offset = 0) {
		return Pattern<const char*>(src + offset, src + offset + length);
	}

	template<size_t N>
	Pattern<const char*> pattern(const char src[N]) {
		return Pattern<const char*>(src, N, 0);
	}


	template <typename TContainer, typename TPredicate>
	void split_str(const std::string &str, TContainer &output, 
		TPredicate pred, bool removeEmpty = true) {

		if (!str.empty()) {
			typedef typename TContainer::value_type ValueType;

			for(std::string::const_iterator it, 
				it_prev = str.begin(), it_end = str.end();;) {

				it = std::find_if(it_prev, it_end, pred);

				if (it != it_prev || !removeEmpty) {
					output.push_back(ValueType(it_prev, it));
				}
				if (it == it_end) {
					return;
				}
				it_prev = it + 1;
			}
		}
	}

	template <typename TContainer>
	void split_str(const std::string &str, TContainer &output, 
		int (*pred)(int), bool removeEmpty = true) {

		split_str(str, output, std::ptr_fun(pred), removeEmpty);
	}


	template <typename TPredicate>
	void strip_str(std::string &str, TPredicate pred) {
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(pred)));
		str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(pred)).base(), str.end());
	}

	template <>
	void strip_str(std::string &str, int (*pred)(int)) {
		strip_str(str, std::ptr_fun(pred));
	}

	template <typename TPredicate>
	std::string trim_str(const std::string &str, TPredicate pred) {
		std::string result = str;
		{
			strip_str(result, pred);
		}
		return result;
	}
}

#endif // UTILS_H_