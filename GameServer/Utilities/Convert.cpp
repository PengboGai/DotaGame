#include <stdlib.h>
#include "Convert.h"

namespace Utilities {

Convert::Convert()
{
}

Convert::~Convert()
{
}

std::string Convert::ToString(bool b)
{
	return b ? "true" : "false";
}

std::string Convert::ToString(float f)
{
	return Convert::ToString<float>("%0.2f", f);
}

std::string Convert::ToString(double d)
{
	return Convert::ToString<double>("%0.2lf", d);
}

std::string Convert::ToString(char c)
{
	return Convert::ToString((long)c);
}

std::string Convert::ToString(unsigned char c)
{
	return Convert::ToString((unsigned long)c);
}

std::string Convert::ToString(short s)
{
	return Convert::ToString((long)s);
}

std::string Convert::ToString(unsigned short s)
{
	return Convert::ToString((unsigned long)s);
}

std::string Convert::ToString(int n)
{
	return Convert::ToString((long)n);
}

std::string Convert::ToString(unsigned int n)
{
	return Convert::ToString((unsigned long)n);
}

std::string Convert::ToString(long l)
{
	return Convert::ToString<long>("%ld", l);
}

std::string Convert::ToString(unsigned long l)
{
	return Convert::ToString<unsigned long>("%lu", l);
}

std::string Convert::ToString(long long l)
{
	return Convert::ToString<long long>("%lld", l);
}

std::string Convert::ToString(unsigned long long l)
{
	return Convert::ToString<unsigned long long>("%llu", l);
}

std::string Convert::ToString(time_t t, TimeFormat format)
{
	struct tm tp;
	localtime_s(&tp, &t);
	return ToString(&tp, format);
}

std::string Convert::ToString(struct tm* tp, TimeFormat format)
{
	std::string str;
	if (format == TimeFormat::HHMMSS) {
		char tmp[100] = { 0 };
		sprintf_s(tmp, sizeof(tmp), "%02d:%02d:%02d",
			tp->tm_hour, tp->tm_min, tp->tm_sec);
		str = tmp;
	}
	else if (format == TimeFormat::YYYYMMDD) {
		char tmp[100] = { 0 };
		sprintf_s(tmp, sizeof(tmp), "%d-%02d-%02d",
			tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);
		str = tmp;
	}
	else if (format == TimeFormat::YYYYMMDDHHMMSS) {
		char tmp[100] = { 0 };
		sprintf_s(tmp, sizeof(tmp), "%d-%02d-%02d %02d:%02d:%02d",
			tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday,
			tp->tm_hour, tp->tm_min, tp->tm_sec);
		str = tmp;
	}
	return str;
}

bool Convert::ToBoolean(const std::string& s)
{
	return s == "true";
}

float Convert::ToFloat(const std::string& s)
{
	return strtof(s.c_str(), nullptr);
}

double Convert::ToDouble(const std::string& s)
{
	return strtod(s.c_str(), nullptr);
}

char Convert::ToChar(const std::string& s)
{
	return (char)ToInt32(s);
}

unsigned char Convert::ToUChar(const std::string& s)
{
	return (unsigned char)ToInt32(s);
}

short Convert::ToInt16(const std::string& s)
{
	return (short)ToInt32(s);
}

unsigned short Convert::ToUInt16(const std::string& s)
{
	return (unsigned short)ToInt32(s);
}

long Convert::ToInt32(const std::string& s)
{
	return strtol(s.c_str(), nullptr, 10);
}

unsigned long Convert::ToUInt32(const std::string& s)
{
	return strtoul(s.c_str(), nullptr, 10);
}

long long Convert::ToInt64(const std::string& s)
{
	return strtoll(s.c_str(), nullptr, 10);
}

unsigned long long Convert::ToUInt64(const std::string& s)
{
	return strtoull(s.c_str(), nullptr, 10);
}

} // namespace Utilities