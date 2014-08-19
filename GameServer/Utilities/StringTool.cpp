#include <stdarg.h>
#include <stdlib.h>
#include "StringTool.h"

namespace Utilities {

StringTool::StringTool()
{
}

StringTool::~StringTool()
{
}

std::string StringTool::Trim(const std::string& s)
{
	std::string output = s;
	output.erase(0, output.find_first_not_of(' '));
	output.erase(output.find_last_not_of(' ') + 1);
	return output;
}

std::string StringTool::TrimStart(const std::string& s)
{
	std::string output = s;
	output.erase(0, output.find_first_not_of(' '));
	return output;
}

std::string StringTool::TrimEnd(const std::string& s)
{
	std::string output = s;
	output.erase(output.find_last_not_of(' ') + 1);
	return output;
}

std::string StringTool::ToLower(const std::string& s)
{
	std::string output;
	for (unsigned int i = 0; i < s.size(); ++i) {
		output.push_back(tolower(s[i]));
	}
	return output;
}

std::string StringTool::ToUpper(const std::string& s)
{
	std::string output;
	for (unsigned int i = 0; i < s.size(); ++i) {
		output.push_back(toupper(s[i]));
	}
	return output;
}

std::string StringTool::Format(const char* format, ...)
{
	std::string ret;
	va_list ap;
	va_start(ap, format);
	char* buf = new char[1024];
	if (buf) {
		vsnprintf_s(buf, 1024, _TRUNCATE, format, ap);
		ret = buf;
		delete[] buf;
	}
	va_end(ap);
	return ret;
}

std::vector<std::string> StringTool::Split(const std::string& str, const std::string& spliter)
{
	std::vector<std::string> output;
	std::string::size_type pos;
	std::string tmp = str + spliter;
	std::size_t size = tmp.size();
	for (std::size_t i = 0; i < size; ++i) {
		pos = tmp.find(spliter, i);
		if (pos < size) {
			std::string s = tmp.substr(i, pos - i);
			output.push_back(s);
			i = pos + spliter.size() - 1;
		}
	}
	return std::move(output);
}

} // namespace Utilities