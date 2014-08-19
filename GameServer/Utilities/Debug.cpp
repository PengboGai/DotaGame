#include <stdarg.h>
#include <stdio.h>
#include <string>
#include "Debug.h"

namespace Utilities {

Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::Log(const char* format, ...)
{
#ifdef _DEBUG
	char tmp[2048] = { 0 };
	va_list ap;
	va_start(ap, format);
	vsnprintf_s(tmp, sizeof(tmp), format, ap);
	va_end(ap);
	std::string s = tmp;
	s += "\n";
	fprintf(stdout, s.c_str());
#endif
}

} // namespace Utilities