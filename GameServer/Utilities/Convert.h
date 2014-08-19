#ifndef _UTILITIES_CONVERT_H_
#define _UTILITIES_CONVERT_H_

#include <string>
#include <time.h>

namespace Utilities {

enum class TimeFormat
{
	HHMMSS,
	YYYYMMDD,
	YYYYMMDDHHMMSS
};

class Convert
{
protected:
	Convert();
	~Convert();

public:
	static std::string ToString(bool b);
	static std::string ToString(float f);
	static std::string ToString(double d);
	static std::string ToString(char c);
	static std::string ToString(unsigned char c);
	static std::string ToString(short s);
	static std::string ToString(unsigned short s);
	static std::string ToString(int n);
	static std::string ToString(unsigned int n);
	static std::string ToString(long l);
	static std::string ToString(unsigned long l);
	static std::string ToString(long long l);
	static std::string ToString(unsigned long long l);
	static std::string ToString(time_t t, TimeFormat format);
	static std::string ToString(struct tm* tp, TimeFormat format);

	static bool ToBoolean(const std::string& s);
	static float ToFloat(const std::string& s);
	static double ToDouble(const std::string& s);
	static char ToChar(const std::string& s);
	static unsigned char ToUChar(const std::string& s);
	static short ToInt16(const std::string& s);
	static unsigned short ToUInt16(const std::string& s);
	static long ToInt32(const std::string& s);
	static unsigned long ToUInt32(const std::string& s);
	static long long ToInt64(const std::string& s);
	static unsigned long long ToUInt64(const std::string& s);

protected:
	template<typename T>
	static std::string ToString(const std::string& fromat, T value)
	{
		char tmp[100] = { 0 };
		sprintf_s(tmp, sizeof(tmp), fromat.c_str(), value);
		return tmp;
	}
};

}; // namespace Utilities

#endif // _UTILITIES_CONVERT_H_