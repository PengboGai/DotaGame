#ifndef _UTILITIES_STRING_TOOL_H_
#define _UTILITIES_STRING_TOOL_H_

#include <string>
#include <vector>

namespace Utilities {

class StringTool
{
protected:
	StringTool();
	~StringTool();

public:
	static std::string Trim(const std::string& s);
	static std::string TrimStart(const std::string& s);
	static std::string TrimEnd(const std::string& s);

	static std::string ToLower(const std::string& s);
	static std::string ToUpper(const std::string& s);

	static std::string Format(const char* format, ...);

	static std::vector<std::string> Split(const std::string& str, const std::string& spliter);
};

}; // namespace Utilities

#endif // _UTILITIES_STRING_TOOL_H_