#ifndef COUNTOF_H_
#define COUNTOF_H_

template <typename T, size_t N>
char (&countof__(const T (&)[N]))[N];

#define countof(arr) \
	sizeof(countof__(arr))

#endif // COUNTOF_H_